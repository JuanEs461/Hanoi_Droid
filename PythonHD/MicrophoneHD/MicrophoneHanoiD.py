# This code is to test the speech recognition together with the serial communication
# By: Juan Ochoa
# 6/11/2023

# Import the required libraries
import serial
import serial.tools.list_ports
import speech_recognition as sr

# Function to select the COM port for the Arduino
def select_port():
    # Get a list of available COM ports
    ports = serial.tools.list_ports.comports()
    ports_list = []

    # Iterate through available ports and display them
    for port in ports:
        ports_list.append(str(port))
        print(str(port))

    # Prompt the user to select a COM port
    val = input('Select Port: COM')
    for i in range(len(ports_list)):
        # Check if the selected port matches the user input
        if ports_list[i].startswith(f'COM{val}'):
            port_var = f'COM{val}'
            print(port_var)
            return port_var

# Function to perform speech recognition
def recognize_speech():
    recognizer = sr.Recognizer() 

    # Use the microphone as the audio source
    with sr.Microphone() as source:
        print("Say 'Start' to begin.")
        # Adjust for ambient noise and capture audio
        recognizer.adjust_for_ambient_noise(source, duration=1)
        audio = recognizer.listen(source)

    try:
        # Attempt to recognize speech using Google Speech Recognition
        word = recognizer.recognize_google(audio).lower()
        print(f"Recognized: {word}")
        return word
    except sr.UnknownValueError:
        print("Speech Recognition could not understand audio.")
        return None
    except sr.RequestError as e:
        print(f"Could not request results from Google Speech Recognition service; {e}")
        return None

# Main program
if __name__ == "__main__":
    # Select the COM port for the Arduino
    arduino_port = select_port()

    # Create a Serial instance for communication with Arduino
    serial_inst = serial.Serial()
    serial_inst.baudrate = 9600
    serial_inst.port = arduino_port
    serial_inst.open()

    # Continuous loop for speech recognition
    while True:
        # Get the recognized command from the speech
        command = recognize_speech()

        # Check the recognized command
        if command == 'start':
            print("Sending 'S' to Arduino.")
            # Send 'S' to the Arduino
            serial_inst.write('S'.encode('utf-8'))
            # Break out of the loop after sending 'S' to the Arduino
            break
        elif command == 'exit':
            print("Exiting program.")
            # Close the serial connection and exit the program
            serial_inst.close()
            exit(0)
