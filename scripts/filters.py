from abc import ABCMeta, abstractmethod 

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
    """
            Remove control characters
    """
    def __init__(self):
        self.description = "Remove control characters"
        self.name = "RMCC"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data:  re.sub('\s+',' ', data))
        return pdf



class Rm_puntuacion(Filter):
    """
             Remove punctuation
    """
    def __init__(self):
        self.description = "Remove punctuation characters"
        self.name = "RMPC"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data: data.translate(str.maketrans('','',string.punctuation)))
        return pdf



class Rm_numeric(Filter):
    """
        Remove numeric values
    """
    def __init__(self):
        self.description = "Remove numeric characters"
        self.name = "RMNC"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data: data.translate(str.maketrans('','','1234567890')))
        return pdf



class Rm_special(Filter):
    """
        Remove special characters (non alphanumeric)
    """
    def __init__(self):
        self.description = "Remove special characters"
        self.name = "RMSC"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data: re.sub(u"[^a-zA-Z0-9áéíóúÁÉÍÓÚâêîôÂÊÎÔãõÃÕçÇ: ]",r"",data))
        return pdf
        # pdf[column] = pdf[column].apply(lambda data: re.sub(u"[-()\"#/@;:<>{}`+=~|.!?,]",r"",data))



class To_lower_case(Filter):
    """
        Transform strings to lower case
    """
    def __init__(self):
        self.description = "Transform strings to lower case"
        self.name = "TTLC"

    def apply(self, pdf, column):
        pdf[column] = pdf[column].apply(lambda data: data.lower())
        return pdf
