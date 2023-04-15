#!/bin/python3

from abc import ABCMeta, abstractmethod 
import re
import pandas as pd


class Filter(object):


    def __init__(self):
        self.description = None
        self.name = None


    def _description():             # Gets the filter description
        return self.description


    def _name(self):                # Gets the filter name
        return self.name


    def __label_helper__(self, data, label, trie, reject):
        """
            Helper function that labels proper names
        """
        name_set = [string for string in data.split() if string in trie and string not in reject]
        if len(name_set) > 0:
            for name in name_set:
                data = re.sub(name, label, data, re.IGNORECASE)
        return data


    @abstractmethod
    def apply(self, pdf, column):   # Interfaz para aplicar .
        pass


# Text Normalization classes

class Rm_control(Filter):
    def __init__(self):
        self.description = "Replace unicode control characters [ \\t\\n\\r\\f\\v]+ with a single white space."
        self.name = "rmcc"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data:  re.sub('\s+',' ', data))
        return pdf



class Rm_puntuacion(Filter):
    def __init__(self):
        self.description = "Remove punctuation characters [!\"#$%%&\'()*+, -./:;<=>?@[\]^_`{|}~]"
        self.name = "rmpc"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data: data.translate(str.maketrans('','',string.punctuation)))
        return pdf



class Rm_numeric(Filter):
    def __init__(self):
        self.description = "Remove numeric characters [0-9]"
        self.name = "rmnc"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data: data.translate(str.maketrans('','','1234567890')))
        return pdf



class Rm_special(Filter):
    def __init__(self):
        self.description = "Remove special characters except [a-zA-Z0-9áéíóúÁÉÍÓÚâêî    ôÂÊÎÔãõÃÕçÇ: ]"
        self.name = "rmsc"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data: re.sub(u"[^a-zA-Z0-9áéíóúÁÉÍÓÚâêîôÂÊÎÔãõÃÕçÇ: ]",r"",data))
        return pdf



class To_lower_case(Filter):
    def __init__(self):
        self.description = "Transform strings to lower case"
        self.name = "ttlc"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data: data.lower())
        return pdf



# Filter factory
class FilterFactory:

    def create(self, atype):
        auto = {
            'rmcc'  : Rm_control(),
            'rmpc'  : Rm_puntuacion(),
            'rmnc'  : Rm_numeric(),
            'rmsc'  : Rm_special(),
            'ttlc'   : To_lower_case()
        }[atype]
        return auto
