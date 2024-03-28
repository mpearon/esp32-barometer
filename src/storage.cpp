#include <Preferences.h>
#include <config.h>
#include <storage.h>

Preferences storage;

void setStoredValue( const char* realm, const char* name, int value ){
	storage.begin( realm, false );
	storage.putUInt( name, value );
	storage.end();
}
int getStoredValue( const char* realm, const char* name ){
	storage.begin( realm, false );
	int returnValue = (storage.getUInt( name, 0 ));
	storage.end();
	return returnValue;
}