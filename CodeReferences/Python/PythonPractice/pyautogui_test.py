#! python3
# formFiller.py - Automatically fills in the form.

import pyautogui, time

# Set these to the correct coordinates for your computer.
nameField = (648, 319)
submitButton = (651, 817)
submitButtonColor = (75, 141, 249)
submitAnotherLink = (760, 224)

for i in range(3):
    pyautogui.click(x=100+100*i, y=217+100*i)
    time.sleep(2)
print("Finish!")