import serial
import time
import statistics

# --- Configuration ---
SERIAL_PORT = 'COM5'     # Change if needed
BAUD_RATE = 9600
authorized_cards = ["0013017111"]

def detect_circular_motion(ser, duration=3):
    """Read MPU6050 data for a few seconds and analyze if motion is circular"""
    print("Perform circular motion now...")
    start_time = time.time()
    x_data, y_data = [], []

    while time.time() - start_time < duration:
        line = ser.readline().decode(errors='ignore').strip()
        if ',' in line:
            try:
                ax, ay, az = [int(v) for v in line.split(',')]
                x_data.append(ax)
                y_data.append(ay)
            except:
                pass

    if len(x_data) < 5:
        print("⚠️ Not enough motion data.")
        return False

    # Compute variation
    x_var = statistics.pstdev(x_data)
    y_var = statistics.pstdev(y_data)

    print(f"X variation: {x_var:.2f}, Y variation: {y_var:.2f}")

    # Circular-like motion has moderate variation in both X and Y
    if x_var > 2000 and y_var > 2000:
        return True
    else:
        return False


def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.\n")

        while True:
            uid = input("Scan your RFID tag: ").strip()
            print(f"UID Detected: {uid}")

            if uid in authorized_cards:
                print("✅ Authorized card! Please perform circular motion...")
                if detect_circular_motion(ser):
                    print("🟢 Motion verified. Access granted.\n")
                    ser.write(b'A')
                else:
                    print("🔴 Motion invalid. Access denied.\n")
                    ser.write(b'D')
            else:
                print("🚫 Unauthorized card. Access denied.\n")
                ser.write(b'D')

            time.sleep(1)

    except serial.SerialException:
        print(f"❌ Could not open port {SERIAL_PORT}. Check your connection.")
    except KeyboardInterrupt:
        print("\nProgram stopped by user.")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial connection closed.")


if __name__ == "__main__":
    main()
