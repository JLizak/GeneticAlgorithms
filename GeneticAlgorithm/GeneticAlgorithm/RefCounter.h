#ifndef CREFCOUNTER_H
#define CREFCOUNTER_H

namespace GA {
    class RefCounter {
    public:
        RefCounter() { i_count; };
        int iAdd() { return ++i_count; };
        int iDec() { return --i_count; };
        int iGet() { return i_count; };

    private:
        int i_count;
    };

}





#endif //CREFCOUNTER_H

