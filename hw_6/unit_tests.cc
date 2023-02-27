#include <chrono>
#include <thread>
#include "stopwatch.h"
#include "random_process.h"
#include "filter.h"
#include "integrator.h"
#include "gtest/gtest.h"
#include <vector>

#define SLEEP std::this_thread::sleep_for(std::chrono::milliseconds(1500))

using namespace std;
using namespace elma;

// TestProcess that sends 0.25 and 0.75 alternately to the link channel
class TestProcess : public Process {
  private:
    int count;

  public:
    TestProcess(string name) : Process(name), count(0) {}

    void init() {}
    void start() {}
    void update() {
        double value = (count % 2 == 0) ? 0.25 : 0.75;
        channel("link").send(value);
        count++;
    }
    void stop() {}
};

namespace {
    //Test function for Stopwatch
    TEST(StopwatchTest, ElapsedTimeTest) {

        Stopwatch w;
        w.start();
        SLEEP;
        w.stop();
        cout<< w.get_seconds() << endl;
        ASSERT_NEAR(w.get_seconds(), 1.5, 0.1);
        SLEEP;
        cout<< w.get_seconds() << endl;
        ASSERT_NEAR(w.get_seconds(), 1.5, 0.1);
        w.start();
        SLEEP;
        w.stop();
        cout<< w.get_seconds() << endl;
        ASSERT_NEAR(w.get_seconds(), 3.0, 0.1);
        w.reset();
        cout<< w.get_seconds() << endl;
        ASSERT_NEAR(w.get_seconds(), 0.0, 0.1);
    }

    //Test function for Random Number Process
    TEST(RandomNumberProcessFilterTest, RunningAverageTest) {
        elma::Manager m;

        RandomProcess r("random numbers");
        Filter f("filter");
        TestProcess t("test");
        Channel link("link");

        m.schedule(t, 1_ms)
        .schedule(f, 1_ms)
        .add_channel(link)
        .init()
        .run(104_ms);

        EXPECT_DOUBLE_EQ(f.value(), 0.5);
    }

    //Test function for Integrator Process
    TEST(IntegratorTest, IntegrationTest) {
      elma::Manager m;

      Integrator integrator("integrator");
      Source source("source", 5.0);
      Channel link("link");
      m.schedule(source, 1_ms)
      .schedule(integrator, 1_ms)
      .add_channel(link)
      .init();

      double expected_integral = 0.0;
      double error_tolerance = 0.001;

      // Test for Constant input
      for (int i = 0; i < 96; i++) {
          expected_integral += source.value() * integrator.delta();
          m.run(2_ms);
          ASSERT_NEAR(integrator.value(), expected_integral, error_tolerance); // Check for ramp function
      }
  }
}