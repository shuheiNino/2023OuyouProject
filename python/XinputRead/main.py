import XInput;
import serial;

def main():
  #confirm python3
  try:
    print("readXInput()")
    readXinput()
  except KeyboardInterrupt:
    print("KeyboardInterrupt")
  finally:
    print("finish")

def readXinput():
  ser = serial.Serial('COM3', 9600)
  LEFTvalue_x = 0
  LEFTvalue_y = 0
  RIGHTvalue_x = 0
  RIGHTvalue_y = 0
  while 1:
    #read XInput value
    events = XInput.get_events()
    for event in events:
      if event.type == XInput.EVENT_CONNECTED:
        print("Controller is successfully connected.\n")  
          
      elif event.type == XInput.EVENT_DISCONNECTED:
        print("Controller is diconnected.\n")

      elif event.type == XInput.EVENT_STICK_MOVED:
        if event.stick == XInput.LEFT:
          #print("LEFTstickpos: (" + str(event.x) + "," + str(event.y) + ")") 
          LEFTvalue_x = event.x
          LEFTvalue_y = event.y
              
        elif event.stick == XInput.RIGHT:
          #print("Rightstickpos: (" + str(event.x) + "," + str(event.y) + ")")
          RIGHTvalue_x = event.x
          RIGHTvalue_y = event.y
        buff = str(LEFTvalue_x) + "," + str(LEFTvalue_y) + "," + str(RIGHTvalue_x) + "," + str(RIGHTvalue_y) + "\n"
        ser.write(buff.encode('utf-8'))
    
    if ser.in_waiting>0:
      serial_value = ser.readline().decode('UTF-8')
      print("受信したデータ: " + serial_value)

if __name__ == "__main__":
  main()

    

    

          
      
      

        
