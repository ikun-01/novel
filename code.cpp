#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Task {
public:
    int powerConsumption;      // 消耗电量
    int minimumInitialCharge;  // 最小初始电量

    Task(int consumption, int initialCharge)
        : powerConsumption(consumption), minimumInitialCharge(initialCharge) {}
};

int calculateMinimumInitialCharge(std::string tasksString) {
    std::vector<Task> tasks;
    
    // 将输入字符串按逗号分隔为任务列表
    std::stringstream ss(tasksString);
    std::string task;
    while (std::getline(ss, task, ',')) {
        // 对于每个任务，按冒号分隔消耗电量和最低初始电量
        std::stringstream task_ss(task);
        std::string powerStr, chargeStr;
        std::getline(task_ss, powerStr, ':');
        std::getline(task_ss, chargeStr, ':');
        
        // 将消耗电量和最低初始电量转换为整数，并创建任务对象
        int power = std::stoi(powerStr);
        int charge = std::stoi(chargeStr);
        Task t(power, charge);
        tasks.push_back(t);
    }
    
    int remainingCharge = 0;  // 剩余电量
    int minimumInitialCharge = 0;  // 最小初始电量
    
    // 遍历每个任务，计算最小初始电量
    for (const auto& task : tasks) {
        // 如果剩余电量不足以完成当前任务，增加最小初始电量
        if (remainingCharge < task.powerConsumption) {
            int chargeToAdd = task.powerConsumption - remainingCharge;
            minimumInitialCharge += chargeToAdd;
            remainingCharge += chargeToAdd;
        }
        
        // 完成当前任务后，减少剩余电量
        remainingCharge -= task.powerConsumption;
    }
    
    // 如果最低初始电量超过了手机的最大电量，则返回-1
    if (minimumInitialCharge > 4800) {
        return -1;
    }
    
    return minimumInitialCharge;
}

int main() {
    std::string tasksString;
    std::cin >> tasksString;

    int minimumInitialCharge = calculateMinimumInitialCharge(tasksString);

    std::cout << minimumInitialCharge << std::endl;

    return 0;
}
