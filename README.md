# About
This applications can be run next to other RoboTeam Twente applications to view and plot all communication. 

# Structure
This application strongly applies the Model-View-Presenter (MVP) pattern:
https://en.wikipedia.org/wiki/Model–view–presenter

View <--- (QT signals and slots) ----> Presenter <------> Model

The idea is that the view and model are completely separated and that they communicate by signals and slots. 
Unfortunately, QT does not allow copying Q_Objects which is a requirement for using the signal/slot syntax.
Therefore every model has a single presenter, which works as a translation unit. A model holds all relevant data while the presenter offers the signals/slots to mutate the model.
Using this structure a model can be copied and for every model a presenter can be either reused or a new one can be created. 



