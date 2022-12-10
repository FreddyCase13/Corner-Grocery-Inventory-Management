FILENAME = 'items.txt'

def readFile(filename):
    '''
    Gets the list of lines read in from the file in raw form.
    @param - the filename to read in (must be in same directory as the Source.cpp!)
    @return - the list of lines
    '''
    
    lines = None
    
    with open('items.txt') as file:
        lines = file.readlines()

    return lines


def getInventory():
    '''
    Get the inventory read in from the file.
    @return - dictionary of inventory in the form {item : frequency}
    '''
    
    # Dictionary of {item : frequency} 
    inventory = {}
    
    items = readFile('items.txt')

    # Loop through the list of items
    for item in items:
        
        # Remove the newline character at end of line. 
        # SEE https://www.delftstack.com/howto/python/python-remove-newline-from-string/
        item = item.strip() 

        # Update existing frequency; otherwise add item to dictionary
        if item in inventory:
            inventory[item] += 1 # accumulate to the dictionary item
        else:
            inventory[item] = 1
            
    return inventory

    
def determineInventory():
    # Get the inventory
    inventory = getInventory()

    # loop through the dictionary's keys(item) and values(fequency)
    # SEE https://stackoverflow.com/questions/3294889/iterating-over-dictionaries-using-for-loops
    for key, value in inventory.items():
    
    # print the output
        print(key, value)


def determineFrequency(item):
    # Get the inventory
    inventory = getInventory()
    
    # Access the item from the inventory
    # SEE https://www.w3schools.com/python/python_dictionaries_access.asp
    x = inventory.get(item)
    return x
    

def output():
    # Very similar to determineInventory 
        # Get the inventory
    inventory = getInventory()
    # Loop through the dictionary and write to the frequency.dat file
    # SEE https://www.w3schools.com/python/python_file_write.asp
    f = open("frequency.dat", "w")
    for key, value in inventory.items():
        f.write(key)
        f.write(" ")
        f.write(str(value))
        f.write("\n")
    f.close()
   
