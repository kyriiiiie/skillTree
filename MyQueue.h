
#define TOTAL_SLOTS 51  // queue size limit

// queue structure
class MyQueue
{
    private:
        int front;
        int rear;
        int size;
        int maxsize;
        int *items;
    public:
        bool isEmpty();
        bool isFull();
        void enqueue(int);
        void dequeue();
        int getSize(){return size;}
        MyQueue(int);
        ~MyQueue();
};

MyQueue::MyQueue(int ms)
{
    maxsize = ms;
    size = 0;
    items = new int[TOTAL_SLOTS];
}

MyQueue::~MyQueue()
{
    delete items;
}

bool MyQueue::isEmpty()
{
    return (size==0);
}

bool MyQueue::isFull()
{
    return (size==maxsize);
}

void MyQueue::enqueue(int data)
{
    if(!isFull())
    {
        size++;
        items[rear] = data;
        rear = (rear+1)%maxsize;
    }
}

void MyQueue::dequeue()
{
    if(!isEmpty())
    {
        size--;
        front=(front+1)%maxsize;
    }
}