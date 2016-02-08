#ifndef pqueue_h
#define pqueue_h

#include <vector>
#include <iostream>

class qcell {
  public:
    double cost;
    int x;
    int y;
    int parent_x; 
	int parent_y;
    qcell(int x, int y, double cost, int parent_x, int parent_y);
    std::ostream &operator<<(std::ostream &out);
    bool operator<(const qcell &other);
    bool operator>(const qcell &other);
    bool operator<=(const qcell &other);
    bool operator>=(const qcell &other);
    bool operator==(const qcell &other);
};

class heap {
  public:
    heap(void);
    ~heap(void);
    void siftup(void);
    void siftdown(void);
    void insert(qcell item);
    qcell remove(void);
    void print(void);
    void swap(int a, int b);
	bool isEmpty();

	std::vector<qcell> queue;
    int n_elem;

};

#endif
