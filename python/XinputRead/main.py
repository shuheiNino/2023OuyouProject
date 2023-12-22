import XInput;
import serial;

def main():
  #confirm python3
  try:
    print("readXInput()")
  except KeyboardInterrupt:
    print("KeyboardInterrupt")
  finally:
    print("finish")

def readXinput():
  while 1:
    #read XInput value
    events = XInput.get_events()
    for event in events:
      if (event.user_index == 1):
        if event.type == XInput.EVENT_CONNECTED:
          print("Controller is successfully connected.\n")  
            
        elif event.type == XInput.EVENT_DISCONNECTED:
          print("Controller is diconnected.\n")

        elif event.type == XInput.EVENT_STICK_MOVED:
          if event.stick == XInput.LEFT:
            print("LEFTstickpos: (" + event.x + "," +event.y + ")") 
            LEFTvalue_x = event.x
            LEFTvalue_y = event.y
                
          elif event.stick == XInput.RIGHT:
            print("Rightstickpos: (" + event.x + "," +event.y + ")")
            RIGHTvalue_x = event.x
            RIGHTvalue_y = event.y

    ser = serial.Serial('COM3', 9600)
    buff = LEFTvalue_x + "," + LEFTvalue_y + "," + RIGHTvalue_x + "," + RIGHTvalue_y
    ser.write(buff)

    

          
      
      

        
