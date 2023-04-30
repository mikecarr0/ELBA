#ifndef DNASEQ_H_
#define DNASEQ_H_

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

class DnaSeq
{
public:
    DnaSeq() : len(), memory(nullptr), ownsmem(true) {}
    DnaSeq(char const *s, size_t len, uint8_t *mem) : len(len), memory(mem), ownsmem(false) { compress(s); }
    DnaSeq(char const *s, size_t len) : len(len), memory(new uint8_t[bytesneeded(len)]), ownsmem(true) { compress(s); }
    DnaSeq(const DnaSeq& rhs) : len(rhs.len), memory(new uint8_t[bytesneeded(rhs.len)]), ownsmem(true) { std::memcpy(memory, rhs.memory, numbytes()); }
    ~DnaSeq() { if (ownsmem) delete[] memory; }

    std::string ascii() const;
    size_t size() const { return len; }
    size_t numbytes() const { return bytesneeded(size()); }
    int remainder() const { return 4*numbytes() - size(); }

    int operator[](size_t i) const;
    bool operator<(const DnaSeq& rhs);
    bool operator==(const DnaSeq& rhs);
    bool operator!=(const DnaSeq& rhs) { return !(*this == rhs); }

    static size_t bytesneeded(size_t numbases) { return (numbases+3)/4; }

    static char    getcodechar(int c)  { return chartab[c]; }
    static uint8_t getcharcode(char c) { return codetab[(int)c]; }
    static char    getcharchar(char c) { return getcodechar(getcharcode(c)); }

    static constexpr char chartab[4+1] = {'A', 'C', 'G', 'T', 'X'};

    static constexpr uint8_t codetab[256] =
    {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 0, 4, 1, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 0, 4,
        4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 0, 4, 1, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 0, 4,
        4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    };

    friend std::ostream& operator<<(std::ostream& stream, const DnaSeq& s)
    {
        stream << s.ascii();
        return stream;
    }

private:
    size_t len; /* number of nucleotides encoded starting at @memory */
    uint8_t *memory; /* each byte encodes up to 8 nucleotides */
    bool ownsmem; /* false if @memory pointer allocated somewhere else */

    /*
     * This is to be used only by the constructors of DnaSeq!
     */
    void compress(char const *s);
};

#endif
