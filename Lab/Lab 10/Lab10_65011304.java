public class Main {
    public static void main(String[] args) {
        BoundedBuffer buffer = new BoundedBuffer();
        Producer producer = new Producer(buffer);
        Consumer consumer = new Consumer(buffer);
        
        producer.start();
        consumer.start();
        
        try {
            producer.join();
            consumer.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class BoundedBuffer {
    private static final int BUFFER_SIZE = 5;
    private int count;
    private int in;
    private int out;
    private Object[] buffer;
    
    public BoundedBuffer() {
        count = 0;
        in = 0;
        out = 0;
        buffer = new Object[BUFFER_SIZE];
    }
    
    public synchronized void insert(Object item) {
        while (count == BUFFER_SIZE) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        
        System.out.println("Producer Entered " + item + " Buffer Size = " + count);
        notifyAll();
    }
    
    public synchronized Object remove() {
        while (count == 0) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        
        Object item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        
        System.out.println("Consumer Consumed " + item + " Buffer Size = " + count);
        notifyAll();
        
        return item;
    }
}

class Producer extends Thread {
    private BoundedBuffer buffer;
    
    public Producer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }
    
    @Override
    public void run() {
        for (int i = 0; i < 20; i++) {
            buffer.insert(i);
            try {
                sleep((int) (Math.random() * 100));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class Consumer extends Thread {
    private BoundedBuffer buffer;
    
    public Consumer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }
    
    @Override
    public void run() {
        for (int i = 0; i < 20; i++) {
            buffer.remove();
            try {
                sleep((int) (Math.random() * 100));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
