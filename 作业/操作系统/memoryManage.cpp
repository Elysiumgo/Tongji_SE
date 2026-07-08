#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// ==========================================
// 模块一：动态分区分配 数据结构与类
// ==========================================
struct MemoryBlock {
    int start_address;
    int size;
    bool is_free;
    int process_id;

    MemoryBlock(int start, int sz, bool free, int pid = -1)
        : start_address(start), size(sz), is_free(free), process_id(pid) {}
};

class DynamicPartitionManager {
private:
    list<MemoryBlock> memory_map;
    int total_size;

public:
    DynamicPartitionManager(int size = 640) : total_size(size) {
        reset();
    }

    void reset() {
        memory_map.clear();
        memory_map.push_back(MemoryBlock(0, total_size, true));
    }

    // 首次适应算法 (First Fit)
    bool allocateFF(int pid, int size) {
        for (auto it = memory_map.begin(); it != memory_map.end(); ++it) {
            if (it->is_free && it->size >= size) {
                if (it->size > size) {
                    // 分割空闲块
                    memory_map.insert(next(it), MemoryBlock(it->start_address + size, it->size - size, true));
                    it->size = size;
                }
                it->is_free = false;
                it->process_id = pid;
                return true;
            }
        }
        return false;
    }

    // 最佳适应算法 (Best Fit)
    bool allocateBF(int pid, int size) {
        auto best_it = memory_map.end();
        int min_waste = total_size + 1;

        for (auto it = memory_map.begin(); it != memory_map.end(); ++it) {
            if (it->is_free && it->size >= size) {
                int waste = it->size - size;
                if (waste < min_waste) {
                    min_waste = waste;
                    best_it = it;
                }
            }
        }

        if (best_it != memory_map.end()) {
            if (best_it->size > size) {
                memory_map.insert(next(best_it), MemoryBlock(best_it->start_address + size, best_it->size - size, true));
                best_it->size = size;
            }
            best_it->is_free = false;
            best_it->process_id = pid;
            return true;
        }
        return false;
    }

    // 回收内存并合并相邻空闲块
    bool deallocate(int pid) {
        bool found = false;
        for (auto& block : memory_map) {
            if (!block.is_free && block.process_id == pid) {
                block.is_free = true;
                block.process_id = -1;
                found = true;
            }
        }

        if (!found) return false;

        // 合并相邻的空闲块
        auto it = memory_map.begin();
        while (it != memory_map.end()) {
            auto next_it = next(it);
            if (next_it != memory_map.end() && it->is_free && next_it->is_free) {
                it->size += next_it->size;
                memory_map.erase(next_it);
            } else {
                ++it;
            }
        }
        return true;
    }

    // 打印当前空闲分区链状态
    void printState() {
        cout << "\n当前内存分区状态:\n";
        cout << "---------------------------------------------------------\n";
        cout << "| 起始地址 |   大小   |   状态   | 占用进程(PID) |\n";
        cout << "---------------------------------------------------------\n";
        for (const auto& block : memory_map) {
            cout << "| " << setw(8) << block.start_address 
                 << " | " << setw(8) << block.size 
                 << " | " << setw(8) << (block.is_free ? "Free" : "Busy") 
                 << " | " << setw(13) << (block.is_free ? "-" : to_string(block.process_id)) << " |\n";
        }
        cout << "---------------------------------------------------------\n";
    }
};


// ==========================================
// 模块二：请求调页存储管理 核心类
// ==========================================
class PageReplacementSimulator {
private:
    vector<int> instructions; // 320条指令流

    // 严格遵循 50-25-25 原则生成指令访问次序
    void generateInstructions() {
        instructions.clear();
        while (instructions.size() < 320) {
            // 1. 在 0 到 319 之间随机选取一个起始执行指令 m
            int m = rand() % 320;
            instructions.push_back(m);

            // 2. 顺序执行下一条指令 m + 1
            if (m + 1 < 320) instructions.push_back(m + 1);

            // 3. 跳转到前地址部分 0 到 m - 1 中的某个指令 m1
            if (m > 0) {
                int m1 = rand() % m;
                instructions.push_back(m1);
                
                // 4. 顺序执行下一条指令 m1 + 1
                if (m1 + 1 < 320) instructions.push_back(m1 + 1);

                // 5. 跳转到后地址部分 m1 + 2 到 319 中的某个指令 m2
                if (319 - (m1 + 2) > 0) {
                    int m2 = (m1 + 2) + rand() % (319 - (m1 + 2) + 1);
                    instructions.push_back(m2);

                    // 6. 顺序执行下一条指令 m2 + 1
                    if (m2 + 1 < 320) instructions.push_back(m2 + 1);
                }
            }
        }
        if (instructions.size() > 320) {
            instructions.resize(320); // 截断保持正好 320 条
        }
    }

public:
    PageReplacementSimulator() {
        generateInstructions();
    }

    // 重新生成指令流
    void regenerate() {
        generateInstructions();
    }

    // FIFO 算法模拟
    void runFIFO() {
        vector<int> frames(4, -1); // 4个物理块，初始化为 -1 表示空闲
        int page_faults = 0;
        int pointer = 0; // 循环队列指针，指向最早进入的物理块

        cout << "\n--- 开始 FIFO 页面置换模拟 ---\n";
        for (int i = 0; i < 320; ++i) {
            int ins = instructions[i];
            int page_no = ins / 10;
            int offset = ins % 10;
            bool hit = false;
            int current_frame = -1;

            // 检查是否命中
            for (int f = 0; f < 4; ++f) {
                if (frames[f] == page_no) {
                    hit = true;
                    current_frame = f;
                    break;
                }
            }

            if (hit) {
                int physical_addr = current_frame * 10 + offset;
                // 为了防止控制台刷屏，这里只详细打印前10步作为演示，最后输出整体结果
                if (i < 10) {
                    cout << "指令 " << setw(3) << ins << " (页 " << setw(2) << page_no << ", 偏移 " << offset 
                         << ") -> 命中! 物理地址: " << setw(2) << physical_addr << " | 内存块状态: [";
                    for(int f=0; f<4; ++f) cout << (frames[f] == -1 ? "空" : to_string(frames[f])) << (f==3?"":" ");
                    cout << "]\n";
                }
            } else {
                page_faults++;
                // 寻找是否有空闲块
                bool placed = false;
                for (int f = 0; f < 4; ++f) {
                    if (frames[f] == -1) {
                        frames[f] = page_no;
                        placed = true;
                        if (i < 10) {
                            cout << "指令 " << setw(3) << ins << " (页 " << setw(2) << page_no << ") -> 缺页(调入) | 内存块状态: [";
                            for(int k=0; k<4; ++k) cout << (frames[k] == -1 ? "空" : to_string(frames[k])) << (k==3?"":" ");
                            cout << "]\n";
                        }
                        break;
                    }
                }

                // 满了，触发 FIFO 置换
                if (!placed) {
                    int replaced_page = frames[pointer];
                    frames[pointer] = page_no;
                    if (i < 10) {
                        cout << "指令 " << setw(3) << ins << " (页 " << setw(2) << page_no << ") -> 缺页(置换页 " << setw(2) << replaced_page << ") | 内存块状态: [";
                        for(int k=0; k<4; ++k) cout << (frames[k] == -1 ? "空" : to_string(frames[k])) << (k==3?"":" ");
                        cout << "]\n";
                    }
                    pointer = (pointer + 1) % 4; // 移动到下一个最早进入的块
                }
            }
        }
        cout << "... (省略后 310 条指令的详细输出) ...\n";
        cout << "【FIFO 结果】总缺页次数: " << page_faults << " 次，缺页率: " 
             << fixed << setprecision(2) << (double)page_faults / 320.0 * 100.0 << "%\n";
    }

    // LRU 算法模拟
    void runLRU() {
        vector<int> frames(4, -1);
        vector<int> time_stamp(4, 0); // 记录每个物理块最近一次被访问的时间（用步数计数表示）
        int page_faults = 0;

        cout << "\n--- 开始 LRU 页面置换模拟 ---\n";
        for (int i = 0; i < 320; ++i) {
            int ins = instructions[i];
            int page_no = ins / 10;
            int offset = ins % 10;
            bool hit = false;
            int current_frame = -1;

            for (int f = 0; f < 4; ++f) {
                if (frames[f] == page_no) {
                    hit = true;
                    current_frame = f;
                    time_stamp[f] = i; // 更新访问时间戳
                    break;
                }
            }

            if (hit) {
                int physical_addr = current_frame * 10 + offset;
                if (i < 10) {
                    cout << "指令 " << setw(3) << ins << " (页 " << setw(2) << page_no << ", 偏移 " << offset 
                         << ") -> 命中! 物理地址: " << setw(2) << physical_addr << " | 内存块状态: [";
                    for(int f=0; f<4; ++f) cout << (frames[f] == -1 ? "空" : to_string(frames[f])) << (f==3?"":" ");
                    cout << "]\n";
                }
            } else {
                page_faults++;
                bool placed = false;
                for (int f = 0; f < 4; ++f) {
                    if (frames[f] == -1) {
                        frames[f] = page_no;
                        time_stamp[f] = i; // 设置初始时间戳
                        placed = true;
                        if (i < 10) {
                            cout << "指令 " << setw(3) << ins << " (页 " << setw(2) << page_no << ") -> 缺页(调入) | 内存块状态: [";
                            for(int k=0; k<4; ++k) cout << (frames[k] == -1 ? "空" : to_string(frames[k])) << (k==3?"":" ");
                            cout << "]\n";
                        }
                        break;
                    }
                }

                // 满了，寻找最近最久未使用的页进行置换（即 time_stamp 最小的那个）
                if (!placed) {
                    int lru_frame = 0;
                    int min_time = time_stamp[0];
                    for (int f = 1; f < 4; ++f) {
                        if (time_stamp[f] < min_time) {
                            min_time = time_stamp[f];
                            lru_frame = f;
                        }
                    }

                    int replaced_page = frames[lru_frame];
                    frames[lru_frame] = page_no;
                    time_stamp[lru_frame] = i; // 更新新页面的时间戳

                    if (i < 10) {
                        cout << "指令 " << setw(3) << ins << " (页 " << setw(2) << page_no << ") -> 缺页(置换页 " << setw(2) << replaced_page << ") | 内存块状态: [";
                        for(int k=0; k<4; ++k) cout << (frames[k] == -1 ? "空" : to_string(frames[k])) << (k==3?"":" ");
                        cout << "]\n";
                    }
                }
            }
        }
        cout << "... (省略后 310 条指令的详细输出) ...\n";
        cout << "【LRU 结果】总缺页次数: " << page_faults << " 次，缺页率: " 
             << fixed << setprecision(2) << (double)page_faults / 320.0 * 100.0 << "%\n";
    }
};


// ==========================================
// 主函数：控制台菜单交互
// ==========================================
int main() {
    system("chcp 65001");
    srand(static_cast<unsigned int>(time(nullptr))); // 初始化随机种子
    
    DynamicPartitionManager partition_manager(640);
    PageReplacementSimulator page_simulator;

    int choice;
    while (true) {
        cout << "\n=========================================\n";
        cout << "       操作系统内存管理模拟系统          \n";
        cout << "=========================================\n";
        cout << " 1. 动态分区分配 - 首次适应算法 (FF)\n";
        cout << " 2. 动态分区分配 - 最佳适应算法 (BF)\n";
        cout << " 3. 请求调页存储模拟 (FIFO 与 LRU 对比)\n";
        cout << " 4. 退出系统\n";
        cout << "=========================================\n";
        cout << "请输入您的选择 (1-4): ";
        cin >> choice;

        if (choice == 4) {
            cout << "感谢使用，系统已退出。\n";
            break;
        }

        switch (choice) {
            case 1: {
                partition_manager.reset();
                cout << "\n--- 首次适应算法 (FF) 模拟 (初始可用空间 640K) ---\n";
                partition_manager.printState();
                
                // 模拟一连串分配回收流，展示动态分区过程
                cout << "\n[操作 1] 进程 1 申请 100K:";
                partition_manager.allocateFF(1, 100);
                partition_manager.printState();

                cout << "\n[操作 2] 进程 2 申请 250K:";
                partition_manager.allocateFF(2, 250);
                partition_manager.printState();

                cout << "\n[操作 3] 释放进程 1 的内存 (100K):";
                partition_manager.deallocate(1);
                partition_manager.printState();

                cout << "\n[操作 4] 进程 3 申请 60K (应填入原进程1留下的空隙中):";
                partition_manager.allocateFF(3, 60);
                partition_map_state: partition_manager.printState();
                break;
            }
            case 2: {
                partition_manager.reset();
                cout << "\n--- 最佳适应算法 (BF) 模拟 (初始可用空间 640K) ---\n";
                
                // 故意制造碎片，对比 BF 算法的优劣
                partition_manager.allocateBF(1, 100);
                partition_manager.allocateBF(2, 200);
                partition_manager.allocateBF(3, 100);
                cout << "初始状态分配：P1(100K), P2(200K), P3(100K)\n";
                partition_manager.printState();

                cout << "\n[操作 1] 同时释放 P1(100K) 和 P3(100K) 的空间:";
                partition_manager.deallocate(1);
                partition_manager.deallocate(3);
                partition_manager.printState();

                cout << "\n[操作 2] 进程 4 申请 90K (BF 会精确寻找最接近90K的空闲块分配):";
                partition_manager.allocateBF(4, 90);
                partition_manager.printState();
                break;
            }
            case 3: {
                // 用相同的指令序列跑两个算法，保证实验对比的严谨性
                page_simulator.regenerate(); 
                page_simulator.runFIFO();
                page_simulator.runLRU();
                break;
            }
            default:
                cout << "无效输入，请重新选择！\n";
        }
    }
    return 0;
}