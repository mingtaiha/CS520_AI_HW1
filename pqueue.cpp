#include "pqueue.h"
#include <iostream>
#include <vector>
#include <cassert>

#define hparent(index) (((index)-1)/2)				// The index of the parent relative to the index of the child 
#define lchild(index) (((index)*2)+1)				// The index of the left child relative to the index of the parent
#define rchild(index) (((index)*2)+2)				// The index of the right child relative to the index of the parent
#define TEST_heap_cpp 0

using namespace std;

qcell::qcell(int x, int y, double cost, int parent_x, int parent_y) {
  this->x = x;										// Setting the x-coordinate of the qcell as the given x value
  this->y = y;										// Setting the y-coordinate of the qcell as the given y value
  this->cost = cost;								// Setting the cost of the qcelll as the given cost
  this->parent_x = parent_x;						// Setting the parent_x as the given parent_x value
  this->parent_y = parent_y;						// Setting the parent_y as the given parent_y value
}

ostream &operator<<(ostream &out, qcell &cell) {	// Overloading the cout operation to print the (x,y) and the cost of a qcell
  out << "[x:" << cell.x << ", " << cell.y << "] = " << cell.cost << endl;
}

bool qcell::operator<(const qcell &other) {			// Overloading the < operator to check if the current cost is less than the
													// 		cost of the other qcell
  return this->cost < other.cost;
}

bool qcell::operator>(const qcell &other) {			// Overloading the > operator to check if the current cost is greater than the
  return this->cost > other.cost;					// 		cost of the other cell
}

bool qcell::operator<=(const qcell &other) {		// Overloading the <= operator to check if the current cost is less than or
  return this->cost <= other.cost;					//		equal to the cost of the other qcell
}

bool qcell::operator>=(const qcell &other) {		// Overloading the >= operator to check if the current cost is less than or
  return this->cost >= other.cost;					//		equal to the cost of the other qcell
}

bool qcell::operator==(const qcell &other) {		// Overloading the == operator to check if the current cost is equal to the
  return this->cost == other.cost;					//		equal to the cost of the other qcell
}

heap::heap(void) {									// Constructor for the heap class
  this->n_elem = 0;									// Sets the number of elements in the heap as 0
}

heap::~heap(void) {									// Destructor for the heap class. Here just in case
}

void heap::swap(int a, int b) {						// Swaps two qcells in the a-th and b-th position of the queue vector
  assert(a >= 0 && b >= 0);							// Checks if the indices are >= 0
  assert(a < queue.size() && b < queue.size());		// Checks if the indices are < the size of the queue vector
  qcell temp = this->queue[a];						// Swapping the two qcells
  this->queue[a] = this->queue[b];
  this->queue[b] = temp;
}

// min heap
void heap::siftup(void) {							// Takes the last element from heap and sifts it up the heap
  int index = this->n_elem-1;						// Set the index to the index of the last element of the queue
  assert(index >= 0);								// Checks whether the heap is empty
  while (index != 0) {								// While the the current index is not head of the heap
    if (this->queue[index].cost < this->queue[hparent(index)].cost) {	// If the cost of the element is greater than that of its parent
      this->swap(index, hparent(index));			// Swap the qcell and its parent qcell based on the indices
      index = hparent(index);						// Set the new index value to index of its parent
    } else {										// Break out if the cost of the parent is greater than or equal to that of the
      break;										// 		current node		
    }
  }
}

void heap::siftdown(void) {							// Takes an element and sifts it down the heap
  if (this->n_elem == 0) {							// Checks to make sure that the heap is nonempty
    return;
  }
  int index = this->n_elem - 1;						// Set the index of the last element to size-1
  int ptr = 0;										// Set the ptr index to zero
  int end = index - 1;								// Set an end value for the while loop
  this->swap(0, index);								// Swap the top element with the last element
  while (ptr < end) {								// Looping until the ptr value is less than the end value
    int new_index = lchild(ptr);					// Set new_index to the index of the left child, assuming it is the smallest
													// 		of the two children
    if (new_index == index) {						// If the new index is equal to the index, then break out of the loop
      break;
    }
													// If the index of the right child of ptr is less than that of the right child
													// 		and the cost of the right child is less than that of ptr value, then
													// 		set the new index to the right child
    if (rchild(ptr) < index && this->queue[lchild(ptr)] > this->queue[rchild(ptr)]) {
      new_index = rchild(ptr);
    }
													// If the new_index is less than the index and the cost of the element of new
    												// 		is less than that of the smallest child, then ...
	if (new_index < index && this->queue[new_index] < this->queue[ptr]) {
      this->swap(ptr, new_index);					// Swap the two elements
      ptr = new_index;								// Set the ptr to new_index to continue checking
    } else {
      break;										// Do nothing otherwise...
    }
  }
}

void heap::insert(qcell item) {						// Insert a qcell item
  if (this->queue.size() == this->n_elem) {			// If the current number of elements is the same is the size of the queue 
    this->queue.push_back(item);					// Add the element to the end of the queue
  } else {
    this->queue[this->n_elem] = item;				// Otherwise, add the element to the queue at th index n_elem
  }
  this->n_elem++;									// Increment the number of elements by one
  this->siftup();									// Sift up
}

qcell heap::remove(void) {							// Remove a qcell item
  if (this->n_elem == 0) {							// If the heap as no elements,
    return qcell(-1, -1, -1, -1, -1);				// Return an qcell (-1, -1, -1, -1, -1)
  } else {
    qcell c = this->queue[0];						// Otherwise, declare a qcell c as the first element of the queue
    this->swap(0, --this->n_elem);					// Swap the first element with the last element of the heap, the decrement
													// 		n_elem by 1
    this->siftdown();								// Sift down
    return c;
  }
}

bool heap::isEmpty() {								// Checks if the heap is empty
	if (this->n_elem == 0) {						// Returns True if empty
		return true;
	} else {										// Returns False if not empty
		return false;
	}
}

void heap::print(void) {							// Prints the heap
  cout << "heap contents:" << endl;
  for (qcell &c : this->queue) {					// Using pass-by-reference variable, loop over every element in the queue (heap)
    cout << c << endl;								// Print the element. The format has been overloaded above
  }
  cout << "end heap print" << endl;
}

#if TEST_heap_cpp

int main() {
  heap h;
  qcell a(0, 0, 1, 0, 0);
  qcell b(0, 0, 2, 0, 0);
  qcell c(0, 0, 3, 0, 0);
  qcell d(0, 0, 4, 0, 0);
  h.print();
  h.insert(a);
  h.insert(b);
  h.insert(c);
  h.insert(d);
  h.print();
  h.swap(0, 1);
  qcell _a = h.remove();
  qcell _b = h.remove();
  qcell _c = h.remove();
  qcell _d = h.remove();
  cout << _a << ", "
       << _b << ", "
       << _c << ", "
       << _d
       << endl;
  return 0;
}

#endif
