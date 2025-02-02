#ifndef INTCELL_H
#define INTCELL_H
class Intcell
{
    private:
        int storedValue;
    public:
        Intcell(int initialValue = 0);
        int read() const;
        void write(int x);
};
#endif // INTCELL_H
