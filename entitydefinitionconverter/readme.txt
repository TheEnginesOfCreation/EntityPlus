EntityDefinitionsConverter (EDC)
================================

This tool converts entity defintion files from the GtkRadiant 1.4 to the GtkRadiant 1.5 format.


Usage
-----
type
edc.exe [filename] [output]
in a command prompt to convert a file. Replace [filename] with the path to the entities.def file that should be converted.
[ouput] should be replaced with the path to which you wish to write the output file (including filename). If [output] is omitted
the resulting entities.ent file will be written to the same folder as where the input file is located.


When this tool is used for definition files other than the ones meant for baseq3 or EntityPlus it may be necessary to add a new
KeyTypes xml file. Because GtkRadiant 1.5 entities.ent files also define the data type for each key, the tool needs to know what
the data type for each key is. Thes KeyTypes xml files tell the tool what datatype is used for what key. To add a new KeyTypes file,
create a new XML file in the KeyTypes folder and add the root element "keytypes". Under the root element, add a node for each new key
where the name of the node is equal to the name of the key. The text within the node should describe the datatype used for this key.

Contact
-------
Visit the EntityPlus project website at http://code.google.com/p/entityplus