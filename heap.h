#ifndef heap_h
#define heap_h

#include <vector>
#include <iostream>

class qcell {
  public:
    double cost;
    int x;
    int y;
    int parent_id; // to be used statically
    qcell(int x, int y, double cost, int parent_id);
    bool operator<(const qcell &other);
    bool operator>(const qcell &other);
    bool operator<=(const qcell &other);
    bool operator>=(const qcell &other);
    bool operator==(const qcell &other);
};

std::ostream &operator<<(std::ostream &out, qcell &cell);

class heap {
  public:
    heap(void);
    ~heap(void);
    void siftup(void);
    void siftdown(void);
    void insert(qcell item);
    qcell remove(void);
    void print(void);

    std::vector<qcell> queue;
    int n_elem;

  private:
    void swap(int a, int b);
};

#endif
