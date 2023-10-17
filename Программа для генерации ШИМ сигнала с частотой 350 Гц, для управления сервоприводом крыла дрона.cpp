#include <chrono>
#include <thread>

const int FREQ = 350; // Частота ШИМ в Гц
const float PERIOD = 1.0f / FREQ; // Период ШИМ в секундах

void pwm() {

  float pulse_width = 1.5f; // Ширина импульса в мс
  
  auto t_next = std::chrono::high_resolution_clock::now();  

  while (1) {

    auto t_now = std::chrono::high_resolution_clock::now();

    // Включить сигнал на pulse_width миллисекунд
    digitalWrite(PIN_SERVO, HIGH);  
    std::this_thread::sleep_for(std::chrono::milliseconds(pulse_width));

    // Выключить сигнал на оставшееся время периода 
    digitalWrite(PIN_SERVO, LOW);
    auto t_sleep = t_next + std::chrono::milliseconds(PERIOD*1000) - t_now;
    std::this_thread::sleep_until(t_sleep); 

    t_next += std::chrono::milliseconds(PERIOD*1000);
  }
}

int main() {
  
  initGPIO();
  
  std::thread pwm_thread(pwm);

  pwm_thread.join();
  
  return 0;
}
