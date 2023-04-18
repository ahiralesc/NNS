# Helper function: loads a text file to a string.
def loadRawData( filename ):
    """
        Procedure for loading an UTF-8 text file
    """
    try:
        with open(filename, 'r', encoding='UTF8') as fp:
            data = fp.read()
    except IOError as e:
        print(e)
    finally:
        fp.close()
    return data



# Helper function: writes a text string to file.
def writeRawData(filename, data):
	"""
		Procedure for writing to an UTF-8 text file
	"""
	try:
		with open(filename, 'w+', encoding='UTF8') as fp:
			fp.write(data)
	except IOError as e:
		print(e)
	finally:
		fp.close()
