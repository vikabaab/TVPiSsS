#include <iostream>
#include <list>
#include <vector>
#include <exception>

struct InternalMemoryAddress {
    size_t segmentNumber;
    size_t offsetFromStart;
};

class InternalMemoryBlock {
public:
    InternalMemoryAddress address{};
    unsigned int size{};
    bool isFree{};
    void *realAddress{};

    InternalMemoryBlock(size_t segmentNum, size_t offsetFromStart,
                        size_t _size, bool _isFree, void *_realAddress) {
        address = InternalMemoryAddress{};
        address.segmentNumber = segmentNum;
        address.offsetFromStart = offsetFromStart;

        size = _size;
        isFree = _isFree;
        realAddress = _realAddress;
    }

};

template<typename T>
class ClientMemoryBlock {
public:
    InternalMemoryAddress address{};
    unsigned int size{};
    bool isFree{};

    ClientMemoryBlock(size_t segmentNum, size_t offsetFromStart,
                      size_t _size, bool _isFree, void *_realAddress, InternalMemoryBlock *_internal) {
        address = InternalMemoryAddress{};
        address.segmentNumber = segmentNum;
        address.offsetFromStart = offsetFromStart;

        size = _size;
        isFree = _isFree;
        realAddress = (T *)_realAddress;
        internal = _internal;
    }

    ClientMemoryBlock() = default;

    ClientMemoryBlock(ClientMemoryBlock<T> const &other) {
        address = other.address;

        size = other.size;
        isFree = other.isFree;
        realAddress = other.realAddress;
        internal = other.internal;
    }

    void Free() {
        isFree = true;
        internal->isFree = true;
    }

    T *GetObject() {
        return realAddress;
    }

    const T *GetObject() const {
        return realAddress;
    }

    void PutObjectInArray(int index) {
        new(realAddress + index) T();
    }

    bool operator==(const ClientMemoryBlock<T>& rhs)
    {
        if (this->realAddress == rhs.realAddress) {
            return true;
        }

        return false;
    }

    bool operator!=(const ClientMemoryBlock<T>& rhs)
    {
        if (this->realAddress != rhs.realAddress) {
            return true;
        }

        return false;
    }

    ClientMemoryBlock<T> operator=(ClientMemoryBlock<T> other)
    {
        address = other.address;
        size = other.size;
        isFree = other.isFree;
        realAddress = other.realAddress;
        internal = other.internal;

        return *this;
    }
private:
    T *realAddress;
    InternalMemoryBlock *internal;

};


class Segment {
public:
    std::byte *memory;
    std::vector<InternalMemoryBlock *> blocks;
    bool isFree;
    size_t maxFreeBlockSize;
    size_t maxFreeBlockAddress;

    const size_t segmentNumber;
    const size_t allocatedMemory;

    Segment(size_t size, size_t segmentNum) : allocatedMemory(size), segmentNumber(segmentNum) {
        memory = static_cast<std::byte *>(malloc(size));
        if (memory == nullptr) {
            throw std::out_of_range("failed to allocate system memory");
        }

        maxFreeBlockSize = size;
        maxFreeBlockAddress = 0;
        isFree = true;

        auto firstBlock = new InternalMemoryBlock(segmentNum, 0, size, true, memory);
        blocks.push_back(firstBlock);
    }

    InternalMemoryBlock *FindAndAllocate(size_t size) {
        for (int i = 0; i < blocks.size(); ++i) {
            if (!blocks[i]->isFree) {
                continue;
            }

            if (blocks[i]->size >= size) {
                AllocateBlock(i, size);

                return blocks[i];
            }
        }

        return nullptr;
    }

    void Free(size_t offsetFromStart) {
        for (int i = 0; i < blocks.size(); ++i) {
            if (blocks[i]->address.offsetFromStart == offsetFromStart) {
                blocks[i]->isFree = true;
                auto freeMemoryStartIndex = i;
                while((freeMemoryStartIndex > 0 && blocks[freeMemoryStartIndex - 1]->isFree)) {
                    --freeMemoryStartIndex;
                }

                size_t allFreeMemory{};
                int freeMemoryEndIndex = freeMemoryStartIndex;
                while (freeMemoryEndIndex < blocks.size() && blocks[freeMemoryEndIndex]->isFree) {
                    allFreeMemory += blocks[freeMemoryEndIndex]->size;
                    freeMemoryEndIndex++;
                }

                if (freeMemoryStartIndex + 1 < freeMemoryEndIndex) {
                    auto firstToDelete = std::next(blocks.begin(), freeMemoryStartIndex + 1);
                    auto lastToDelete = std::next(blocks.begin(), freeMemoryEndIndex);
                    blocks.erase(firstToDelete, lastToDelete);
                }

                blocks[freeMemoryStartIndex]->isFree = true;
                blocks[freeMemoryStartIndex]->size = allFreeMemory;

                return;
            }
        }

        throw std::out_of_range("failed to free not exist memory");
    }

    void PrintAllBlocks() {
        auto i = 0;
        for (auto &block: blocks) {
            printf("\tblock №%i address: (%zu, %zu) with state %s\n", i++, block->address.segmentNumber, block->address.offsetFromStart, block->isFree? "true" : "false");
        }
    }

private:
    void AllocateBlock(int index, size_t needToAlloc) {
        if (!blocks[index]->isFree) {
            throw std::out_of_range("failed to allocate not empty mem");
        }

        blocks[index]->size = needToAlloc;
        blocks[index]->isFree = false;

        if (blocks.size() <= index + 1) {
            auto nextBlockStart = blocks[index]->address.offsetFromStart + blocks[index]->size;
            auto nextBlockSize = allocatedMemory - nextBlockStart;

            auto memBlock = new InternalMemoryBlock(segmentNumber, nextBlockStart, nextBlockSize,
                                                    true, memory + nextBlockStart);

            blocks.push_back(memBlock);
        }
    }
};

class Allocator {
private:
    std::vector<Segment> segments{};

    const unsigned int maxSegmentSize = 2048;

public:
    void PrintAllSegments() {
        auto i = 0;
        for (auto &segment: segments) {
            printf("segment №%i:\n", i++);
            segment.PrintAllBlocks();
        }
    }

    template<typename T>
    ClientMemoryBlock<T> Allocate(size_t size) {
        if (size > maxSegmentSize) {
            throw std::invalid_argument("try allocate more than allowed once time");
        }

        for (auto &segment: segments) {
            auto memory = segment.FindAndAllocate(size);
            if (memory == nullptr) {
                continue;
            }

            ClientMemoryBlock<T> clientBlock = ClientMemoryBlock<T> (
                    memory->address.segmentNumber, memory->address.offsetFromStart, memory->size, memory->isFree, memory->realAddress, memory);

            return clientBlock;
        }

        auto newSegment = Segment(maxSegmentSize, segments.size());
        auto memory = newSegment.FindAndAllocate(size);
        if (memory == nullptr) {
            throw std::out_of_range("failed to allocate memory");
        }

        segments.push_back(newSegment);

        ClientMemoryBlock<T> clientBlock = ClientMemoryBlock<T> (
                memory->address.segmentNumber, memory->address.offsetFromStart, memory->size, memory->isFree, memory->realAddress, memory);

        return clientBlock;
    }

    template<typename T>
    void Free(ClientMemoryBlock<T> &memory_block) {
        if (memory_block.address.segmentNumber > segments.size()) {
            throw std::out_of_range("can't free this memory");
        }

        segments[memory_block.address.segmentNumber].Free(memory_block.address.offsetFromStart);
        memory_block.Free();
    }
};
