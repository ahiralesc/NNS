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
    def apply(self, pdf, column):   # The main interface
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


class Label_regex(Filter):
	def __init__(self):
		self.description = "Label strings that match a regular expression with a given label"
		seld.name = "regex"
		self.regexset = [
(' #AGE_RANGE ',r'\b\d{2,3}\s*(?:[-]\s*\d{2,3}|\+)\s*(?:years)\b'),
(' #AGE_RANGE ',r'\b(?:a(?:ge|ged|ges))\s*\d{1,3}\s*(?:to|through)\s*\d{1,3}\b'),
(' #AGE ',r'\b\d{1,3}\s*[-]?\s*(?:y(?:o|[\.o\.]+|/o|ears old|ear old||ear-old))\b'),
(' #AGE ',r'\b(?:(?:twenty|thirty|forty|fifty|sixty|seventy|eighty|ninety)[-]?(?:one|two|three|four|five|six|seven|eight|nine)?|(?:one|two|three|four|five|six|seven|eight|nine)?[-]?(?:hundred)[-]?(?:and)?[-]?(?:one|two|three|four|five|six|seven|eight|nine)?|(?:zero|ten|eleven|twelve|thirteen|fourteen|fifteen|sixteen|seventeen|eighteen|nineteen|twenty))[-](?:year)[-](?:old)\b'),
(' #AGE ',r'\b\d{2,3}[-](?:year)[-](?:old)\b'),
(' #BLOOD_PRESSURE ',r'\bb(?:lood\s*pressure|p)\s*(?:\:|is|of)\s*\d{2,3}/\d{2,3}\b'),
(' #BLOOD_PRESSURE ',r'\b\d{2,3}/\d{2,3}\s*(?:mmHg)\b'),
(' #DATE ',r'(?:j(?:anuary|an.|an|a)?|f(?:ebruary|eb.|eb)?|m(?:arch|ar.|ar|r)?|a(?:pril|pr.|pr|p)?|m(?:ay|y)?|j(?:une|un|e)?|j(?:uly|ul|l)?a(?:ugust|ug.|ug|g)?|s(?:eptember|ept.|ep)?|o(?:ctober|ct.|ct)?|n(?:ovember|ov.|ov)?|d(?:ecember|ec.|ec)?)\s*\d{1,2},\s*(?:19[5-9]\d|2\d{3}|\d{2})(?=\D|$)'),
(' #DATE ',r'\b(?:(?:0[1-9]|1[012])(?:\D|$)(?:0[1-9]|[12][0-9]|3[01])(?:\D|$)(?:19[1-9]\d|2\d{3}|\d{2}))'),
(' #WEIGHT_RANGE ',r'\b(?:[0-9]*[.])?[0-9]+\s*(?:\-|to)\s*(?:[0-9]*[.])?[0-9]+\s*(?:p(?:ound|ounds)?|l(?:b.|bs|b)?|o(?:unce|unces)?|o(?:z.|z)?|g(?:rains|rams)?)\b' )
(' #WEIGHT ',r'\b(?:[0-9]*[.])?[0-9]+\s*(?:p(?:ound|ounds)?|l(?:b.|bs|b)?|o(?:unce|unces)?|o(?:z.|z)?|g(?:rains|rams)?)\b'),
(' #HEIGHT ',r'\b\d+\s*(?:f(?:t|t.|eet)?|\'),?\s*\d+?\s*(?:i(?:n|n.|nches)|\")?\b'),
(' #OXYGEN_SATURATION ',r'(?:svo2|sto2|spo2|sao2)\s*[(]?\s*(?:above|below|of|less than|greater than|was|\<|\:)?\s*[+-]?(?:[0-9]*[.])?[0-9]+\s*(?:±|[\+\/-]+)?\s*(?:[+-]?(?:[0-9]*[.])?[0-9]+)?\s*(?:%|percent)\s*[)]?'),
(' #PULSE ',r'\b(?:pulse|heart)\s*(?:(?:rate)?\s*(?:is|of)?)?\s*\d{2,3}\b'),
(' #RESPIRATORY_RATE ',r'\b(?:\d{2}\s*[-]\s*|<|>)?\d{2}\s*(?:bpm|breaths/min|breaths per minute)\b'),
(' #TEMPERATURE ',r'\b[+-]?(?:[0-9]*[.])?[0-9]+\s*(?:±|[\+\/-]+)?\s*(?:[+-]?(?:[0-9]*[.])?[0-9]+)?\s*(?:°C|°F|degrees)\b')
]

	def apply(self, pdf, column):
		for label, regexp in self.regexset:
			pdf[column] = pdf[column].apply(lambda data: re.sub(regexp, label, data, re.IGNORECASE))
		return pdf


# Filter factory
class FilterFactory:

    def create(self, atype):
        auto = {
            'rmcc'  : Rm_control(),
            'rmpc'  : Rm_puntuacion(),
            'rmnc'  : Rm_numeric(),
            'rmsc'  : Rm_special(),
            'ttlc'   : To_lower_case(),
			'regex' : Label_regex()
        }[atype]
        return auto
