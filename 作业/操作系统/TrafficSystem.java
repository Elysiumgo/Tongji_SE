import java.util.concurrent.Semaphore;

public class TrafficSystem {
    // 信号灯状态：东西绿灯 或 南北绿灯
    static volatile String greenDirection = "东西"; 
    // 互斥锁：模拟单车道，确保“不准超车”，车辆按序通过
    static Semaphore roadMutex = new Semaphore(1); 

    static class Vehicle extends Thread {
        String dir;  // 来源方向：东, 西, 南, 北
        String type; // 车辆类型
        int id;

        public Vehicle(String dir, String type, int id) {
            this.dir = dir;
            this.type = type;
            this.id = id;
        }

        @Override
        public void run() {
            try {
                boolean isSpecial = !type.equals("普通车");

                // --- 逻辑1：红灯等待（阻塞） ---
                // 如果不是特种车，且当前方向不是绿灯，则进入循环等待（排队）
                if (!isSpecial) {
                    while (!greenDirection.contains(dir)) {
                        // 模拟普通车辆在停止线前熄火等待
                        Thread.sleep(500); 
                    }
                }

                // --- 逻辑2：按序通行（互斥） ---
                // P(roadMutex): 获取路权，确保前车没走完后车不能动（不准超车）
                roadMutex.acquire(); 
                System.out.println("【" + type + id + "】(" + dir + "向) 正在通过路口... [当前灯号：" + greenDirection + "绿灯]");
                Thread.sleep(1000); // 模拟通过时间
                System.out.println("【" + type + id + "】已离开路口。");
                roadMutex.release(); // V(roadMutex)

            } catch (InterruptedException e) { e.printStackTrace(); }
        }
    }

    public static void main(String[] args) {
        // 信号灯控制线程：每8秒切换一次
        new Thread(() -> {
            try {
                while (true) {
                    greenDirection = "东西";
                    System.out.println("\n>>>> 信号灯：东西向【绿灯】, 南北向【红灯】 (持续8秒) <<<<");
                    Thread.sleep(8000); 
                    
                    greenDirection = "南北";
                    System.out.println("\n>>>> 信号灯：南北向【绿灯】, 东西向【红灯】 (持续8秒) <<<<");
                    Thread.sleep(8000);
                }
            } catch (InterruptedException e) { e.printStackTrace(); }
        }).start();

        // 模拟真实车流：源源不断的普通车，极少数特种车
        new Thread(() -> {
            for (int i = 1; i <= 30; i++) {
                String[] dirs = {"东", "西", "南", "北"};
                String d = dirs[i % 4];
                // 每6辆车里才可能出现一辆特种车
                String t = (i % 6 == 0) ? "消防车" : "普通车"; 
                new Vehicle(d, t, i).start();
                try { Thread.sleep(800); } catch (Exception e) {} // 车辆到达间隔
            }
        }).start();
    }
}