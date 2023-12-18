import cv2
import serial
import time
import numpy as np

# Initialize the serial connection to Arduino
arduino = serial.Serial('COM5', 9600)  # Replace 'COM_PORT' with your Arduino's port
time.sleep(2)  # Wait for the connection to establish

# Load the Haar Cascade Classifier for face detection
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

# Initialize the video capture object
cap = cv2.VideoCapture(0)

# Set the rest position for the servos
rest_position = 90
arduino.write(f"{rest_position},{rest_position}\n".encode())

def get_random_color():
    color = list(np.random.random(size=3) * 256)
    return int(color[0]), int(color[1]), int(color[2])

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    if not ret:
        break

    # Convert the frame to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect faces in the grayscale frame
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # Draw rectangles around the faces
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), get_random_color(), 2)
        cv2.putText(frame, "Detecting face", (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, get_random_color(), 2)

        # Calculate servo positions based on the face position
        servoX_position = int((x + w/2) * 180 / frame.shape[1])
        servoY_position = int((y + h/2) * 180 / frame.shape[0])

        # Send the servo positions to the Arduino
        arduino.write(f"{servoX_position},{servoY_position}\n".encode())
        break  # Only send the position of the first detected face

    # Display the resulting frame
    cv2.imshow('Frame', frame)

    # Break the loop with the 'q' key
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
cap.release()
cv2.destroyAllWindows()