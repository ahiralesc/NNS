
import json
import zipfile
import pandas as pd
import constants

class Dataset(object):
    def __init__(self):
        self.pdf = None
    
    def read_json(self, filename, field=None):
        """
            Loads a JSON formated, UTF-8 character encoded, corpus to a pandas dataframe.
        """
        try:
            with open(filename, encoding="ISO-8859-1") as fp:
                data = json.load(fp)
            if field != None:
                self.pdf = pd.DataFrame(data[field])
            else:
                self.pdf = pd.DataFrame(data)
        except IOError as e:
            print(e)
    
    
    def write_json(self, filename):
        """
            Stores the dataframe content to persistance in JSON format. 
        """
        try:
            with open(filename, 'w', encoding="ISO-8859-1") as fp:
                self.pdf.to_json(fp, force_ascii=False)
        except IOError as e:
            print(e)
    
    
    def read_cvs(self, filename, separator, encode = "ISO-8859-1",  header=False):
        """
            Loads a CVS formated, with UTF-8 character encoding, corpus to a pandas dataframe.
            By specifying header True the first row  is  is assummed to contain the header 
        """
        try:
            if not header:
                self.pdf = pd.read_csv(filename,  keep_default_na=False, sep=separator,  encoding = encode, header=None, engine='python') 
            else: 
                self.pdf = pd.read_csv(filename, keep_default_na=False, sep=separator,  encoding = encode, names = header, engine='python')
        except IOError as e:
            print(e)
    
    
    def write_cvs(self, filename):
        """
            Writes the dataframe to persistance in CSV formated, with UTF-8 character encoding.
        """
        if self.pdf != None:
            self.pdf.to_csv(filename, index=False,  encoding="ISO-8859-1")     # Do not write row names
    
    
    def loadRawData(self, filename):
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


    def writeRawData(self, filename, data):
        """
            Procedure for writing to an UTF-8 text file
        """
        try:
            with open(filename, 'w', encoding='UTF8') as fp:
                fp.write(data)
        except IOError as e:
                print(e)
        finally:
            fp.close()
    
    
    
    def zipRawData(self, source_file, target_file):
        """
            Compresses a source file and stores it in the target file
        """
        with zipfile.ZipFile(target_file, 'w') as cfp:
            cfp.write(source_file)
    

    def categories(self):
        """
            The categories of the corpus.
        """
        return self.pdf.columns
    

    def raw(self, categories = []):
        """
            The raw content of the corpus in a pandas dataframe or the raw content of the 
            specified fields in the pandas dataframe
        """
        if len(categories) == 0:
            return self.pdf
        else:
            return self.pdf[categories]
    
    def set_dataset(self, data):
        """
            Sets the dataset
        """
        self.pdf = data