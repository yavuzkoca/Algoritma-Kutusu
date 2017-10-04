class SmallVector{
public:
    SmallVector();
    SmallVector(int[], int);
    SmallVector(const SmallVector &);
    void push_back(int);
    void push_back(int[], int);
    int pop_back();
    SmallVector reverse() const;
    void print() const;
    SmallVector operator+(const SmallVector &) const;
    SmallVector operator*(int) const;
    int& operator[](int);
    const SmallVector & operator=(const SmallVector &);
    int getSize() const;
    int getCapacity() const;
    ~SmallVector();

private:
    int currSize;
    int capacity;
    int staticBuffer[32];
    int *dynamicBuffer;
};