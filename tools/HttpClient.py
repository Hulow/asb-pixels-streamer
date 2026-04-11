import time
import requests

ESP_IP = "http://192.168.4.1/status"

def wait_for_device(timeout=30):
    print("Waiting for ESP32...")

    start = time.time()
    while time.time() - start < timeout:
        try:
            r = requests.get(ESP_IP, timeout=2)
            if r.status_code == 200:
                print("ESP32 is online!")
                return True
        except:
            pass

        time.sleep(1)

    print("ESP32 not reachable.")
    return False


def httpClient():
    try:
        response = requests.get(ESP_IP)
        print("Response:", response.text)
    except Exception as e:
        print("Error calling endpoint:", e)


if __name__ == "__main__":
    if wait_for_device():
        httpClient()