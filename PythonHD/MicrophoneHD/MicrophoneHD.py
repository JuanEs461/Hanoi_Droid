import serial
import serial.tools.list_ports
import speech_recognition as sr

def select_port():
    ports = serial.tools.list_ports.comports()
    ports_list = []

    for port in ports:
        ports_list.append(str(port))
        print(str(port))

    val = input('Select Port: COM')
    for i in range(len(ports_list)):
        if ports_list[i].startswith(f'COM{val}'):
            port_var = f'COM{val}'
            print(port_var)
            return port_var

def recognize_speech():
    recognizer = sr.Recognizer() 

    with sr.Microphone() as source:
        print("Say 'Start' to begin.")
        recognizer.adjust_for_ambient_noise(source, duration=1)
        audio = recognizer.listen(source)

    try:
        word = recognizer.recognize_google(audio).lower()
        print(f"Recognized: {word}")
        return word
    except sr.UnknownValueError:
        print("Speech Recognition could not understand audio.")
        return None
    except sr.RequestError as e:
        print(f"Could not request results from Google Speech Recognition service; {e}")
        return None

if __name__ == "__main__":
    arduino_port = select_port()

    serial_inst = serial.Serial()
    serial_inst.baudrate = 9600
    serial_inst.port = arduino_port
    serial_inst.open()

    while True:
        command = recognize_speech()

        if command == 'start':
            print("Sending 'S' to Arduino.")
            serial_inst.write('S'.encode('utf-8'))
            # Break out of the loop after sending 'S' to the Arduino
            break
        elif command == 'exit':
            print("Exiting program.")
            serial_inst.close()
            exit(0)
