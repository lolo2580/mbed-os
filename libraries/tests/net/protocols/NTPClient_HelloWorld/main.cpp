#include "mbed.h"
#include "test_env.h"
#include "EthernetInterface.h"
#include "NTPClient.h"

int main()
{
    EthernetInterface eth;
    NTPClient ntp;
    eth.init(); //Use DHCP
    eth.connect();

    // NTP set time
    {
        bool result = true;
        const char *url_ntp_server = "0.pool.ntp.org";
        printf("NTP_SETTIME: Trying to update time... \r\n");
        const int ret = ntp.setTime(url_ntp_server);
        if (ret == 0) {
          time_t ctTime = time(NULL);
          printf("NTP_SETTIME: UTC Time read successfully ... [OK]\r\n");
          printf("NTP_SETTIME: %s\r\n", ctime(&ctTime));
        }
        else {
          printf("NTP_SETTIME: Error(%d) ... [FAIL]\r\n", ret);
          result = false;
        }

        if (result == false) {
            notify_completion(false);
            exit(ret);
        }
    }
    eth.disconnect();
    notify_completion(true);
    return 0;
}
