# This is a sample Python script.
import os


# Press Mayús+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    print_hi('PyCharm')

# See PyCharm help at https://www.jetbrains.com/help/pycharm/

if __name__ == '__main__':
    print_hi('PyCharm')

jose = os.getenv('mi_variable')

if jose:
    print('El valor del mi variable es: ', jose)
else:
    print('El valor de entorno de mi variable no está definida')