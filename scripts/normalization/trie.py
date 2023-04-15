#!/usr/bin/env python

class Trie:
    """
        Trie is a wrapper class for datrie.Trie. It deals with I/O of CSV files.
        See https://pypi.org/project/datrie/
    """
    def __init__(self):
        """ 
            The trie contains the lower case strings. 
        """
        self.trie = datrie.Trie(string.printable)   # trie representation of the dataset

        
    def append(self, pdf, column):
        """
            Appends a dataset to the trie 
        """
        for word in pdf[column]:
            lower_case_word = word.lower()
            if lower_case_word not in self.trie:
                self.trie[lower_case_word] = word

            
    def write_trie(self, filename):
        """
            Save the Trie to persistance.
        """  
        try:
            self.trie.save(filename)
        except IOError as e:
            print(e)
    
    
    def read_trie(self, filename):
        """
            Read the Trie from persistance.
        """  
        try:
            self.trie = datrie.Trie.load(filename)
        except IOError as e:
            print(e)
    
    
    def get_header(self):
        """
            Returns the data set header. 
        """  
        if self.pdf == None:
            return None
        else:
            return self.pdf.columns
    
    
    def get_trie(self):
        """
            Returns the trie data structure. For dictionary operations see https://github.com/pytries/datrie
        """
        return self.trie
