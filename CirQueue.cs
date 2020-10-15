using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;

namespace console.writing
{
    class CirQueue
    {
        private int front, rear;
        private int[] data = new int[5];
        public CirQueue() { for (int i = 0; i < 5; ++i) data[i] = 0; front = rear = 0; }

        public int DeQueue()
        {
            if (rear == front)
                Console.WriteLine("下溢");
            else
            {
                front = (front + 1) % 5;
                return data[front];
            }
            return 0;
        }
        public void EnQueue(int element)
        {
            if (front == (rear + 1) % 5)
                Console.WriteLine("上溢");
            else
            {
                rear = (rear + 1) % 5;
                data[rear] = element;
            }
        }

        public int GetHead()
        {
            if(rear==front)
            {
                Console.WriteLine("这个队列没有元素");
                return 0;
            }
            return data[(front+1)%5];
        }

        public void Empty()
        {
            if (front == rear)
                Console.WriteLine("这个表确实为空");
            else
                Console.WriteLine("这个表不为空");
        }

        public void Show()
        {
            for (int i = ((front + 1) % 5); i <= (rear % 5); i++)
                Console.WriteLine(data[i]);
        }
    }
}
