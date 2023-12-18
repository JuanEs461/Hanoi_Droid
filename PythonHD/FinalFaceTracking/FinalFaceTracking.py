import cv2 # import the OpenCV library
import serial # access the serial port
import random # import the Python random module
import time # import the Python time module
import threading


# Initialize serial communication with Arduino
arduino_serial = serial.Serial('COM10', 115200) # COM7 because that is the one the Arduino Uno is connected to on this PC


# Load the classifier
face_classifier = cv2.CascadeClassifier(
    cv2.data.haarcascades + "haarcascade_frontalface_default.xml" # in quotation marks is a file classifier for detecting frontal faces in an image 
)

video_capture = cv2.VideoCapture(1) # create a video capture object, then specify the camera that will be used


def detect_bounding_box(vid): # define a function that takes a video frame as an argument
    gray_image = cv2.cvtColor(vid, cv2.COLOR_BGR2GRAY) # convert the video to grayscale
    faces = face_classifier.detectMultiScale(gray_image, 1.1, 5, minSize = (40, 40)) # use a face classifier for detecting faces in the grayscale image, then take the image to be searched, 
    # the scale factor, the minimum number of neighbors, and the minimum size of the detected faces
    for (x, y, w, h) in faces: # for the x, y, w, h values returned from the previous line, run the following
        cv2.rectangle(vid, (x, y), (x + w, y + h), (0, 255, 0), 4) # draw a green rectangle on the faces using the cv2.rectangle function, the position and size determined by the x, y, w, h values

        # send face coordinates to the send_to_arduino function below
        send_to_arduino(faces)
        
    return faces # return the list of detected faces as a tuple of x, y, w, h values

def send_to_arduino(faces):
    # Calculations to find the way to move the servo
    #data_to_send = f"{x},{x1},{face_width}\n"
    #arduino_serial.write(data_to_send.encode())
    
    # Initialize variables
    x = x1 = face_width = 0
    
    message = 'X'
    
    if len(faces) > 0:
        random_face = random.choice(faces)
        x, _, w, _ = random_face
        x1 = x + w
        face_width = w
        
        if  (face_width < 50 and x < 290) or (49 < face_width < 100 and x < 265) or (99 < face_width < 150 and x < 240) or (149 < face_width < 200 and x < 215) or (199 < face_width < 250 and x < 195):
            message = 'L'
        elif (face_width < 50 and x1 > 350) or (49 < face_width < 100 and x1 > 375) or (99 < face_width < 150 and x1 > 400) or (149 < face_width < 200 and x1 > 425) or (199 < face_width < 250 and x1 > 445):
            message = 'R'
        elif (face_width < 50 and x > 289 and x1 < 351) or (49 < face_width < 100 and x > 264 and x1 < 376) or (99 < face_width < 150 and x > 239 and x1 < 401) or (149 < face_width < 200 and x > 214 and x1 < 426) or (199 < face_width < 250 and x > 194 and x1 < 446):
            message = 'C'
        
    else:
        message = 'X'
        print("No faces detected. Sending 'X'.")

            
    # Print debug information
    print(f"Face position: {x}, {x1}, Face width: {face_width}")

    # Existing message selection logic...

    print(f"Selected message: {message}")

            
        
    arduino_serial.write(message.encode())
    arduino_serial.write(b'\n')
    
def delayed():
    Message = 'E'
    print(Message)
    arduino_serial.write(Message.encode())
    arduino_serial.write(b'\n')

endTrack = threading.Timer(120, delayed)
endTrack.start()

    

face_detected_prev = False  # Flag to track if a face was detected in the previous iteration

while True:
    result, video_frame = video_capture.read()

    if result is False:
        break

    faces = detect_bounding_box(video_frame)

    cv2.imshow("My Face Detection Project", video_frame)

    # Check if faces are detected and if the status has changed from the previous iteration
    if len(faces) > 0 and not face_detected_prev:
        send_to_arduino(faces)
        face_detected_prev = True
    elif len(faces) == 0 and face_detected_prev:
        send_to_arduino(faces)
        face_detected_prev = False

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

    time.sleep(0.1)

video_capture.release()
cv2.destroyAllWindows()
