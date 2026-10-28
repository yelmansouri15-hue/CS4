from data_structures.sllist import SLList

test = SLList()
test.clear()

def check_int(a):
    try:
        return int(a)
    except ValueError:
        print("Type an integer")

        return False

def choose_index():
    index = check_int(input("Choose an index: "))

    if index is False:
        pass

    return index

def show_array():
    print(test.show())

first_option = 0
last_option = 7

while True:
    print(f"{first_option}. Quit test  1. Get  2. Set  3. Add  4. Remove  5. Push  6. Pop {last_option}. See actual array")

    while True: 
        election = check_int(input("Choose the action by typing its number: "))

        if election is not False and election >= first_option and election <= last_option:
            break

    try:
        match election:
            case 0:
                break

            case 1:
                    index = choose_index()

                    element_get = test.get(index)

                    print(f"The element of the index number {index} is {element_get}")
                    show_array()

            case 2:
                    index = choose_index()
                    element = input("Choose an element to set: ")

                    element_set = test.set(index, element)

                    print(f"{element} set in the index number {index}, replacing {element_set}")
                    show_array()

            case 3:
                    index = choose_index()
                    element = input("Choose an element to add: ")

                    test.add(index, element)

                    print(f"{element} added in the index number {index}")
                    show_array()                    

            case 4:
                    index = choose_index()

                    element_remove = test.remove(index)

                    print(f"{element_remove} removed form the index number {index}")
                    show_array()                    

            case 5:
                element = input("Choose an value to add at the head: ")

                test.push(element)

                print(f"A node with the values {element} is added at the head")
                show_array()

            case 6:
                element_pop = test.pop()

                print(f"The head, with a value of {element_pop}, was removed")
                show_array()

            case 7:
                show_array()
    except IndexError:
        print("Index out of bounds")