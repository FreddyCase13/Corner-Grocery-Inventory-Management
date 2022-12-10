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
    inventory = {}
    
    items = readFile('items.txt')

    for item in items:
        
        item = item.strip() 

        if item in inventory:
            inventory[item] += 1
        else:
            inventory[item] = 1
            
    return inventory

    
def determineInventory():
    '''
    Loops through inventory dictionary and prints each key and value
    '''
    inventory = getInventory()

    for key, value in inventory.items():
        print(key, value)


def determineFrequency(item):
    '''
    Shows the frequency of an item in inventory
    @param - the item that we wish to get the frequency of
    @return - frequency of item in inventory
    '''
    inventory = getInventory()
  
    x = inventory.get(item)
    return x
    

def output():
    '''
    Loops through inventory dictionary, creates 'frequency.dat' file, and writes each key and value to frequency.dat
    '''
    inventory = getInventory()

    f = open("frequency.dat", "w")
    for key, value in inventory.items():
        f.write(key)
        f.write(" ")
        f.write(str(value))
        f.write("\n")
    f.close()
   
