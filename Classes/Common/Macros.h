//
//  Common/Macros.h
//  MyCppGame
//
//  Created by sma11case on 5/13/15.
//
//

#ifndef MyCppGame_Macros_h
#define MyCppGame_Macros_h

#define ADDPROPERTY(varType, varName, setter, getter)\
protected: varType varName;\
public: virtual varType getter(void) const { return varName; }\
public: virtual void setter(varType var){ varName = var; }

#define ADDGETTER(varType, varName, getter)\
public: virtual varType getter(void) const { return varName; }

#define ADDSETTER(varType, varName, setter)\
public: virtual void setter(varType var){ varName = var; }

#endif
