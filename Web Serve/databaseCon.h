#ifndef DATABASECON_H
#define	DATABASECON_H

#include <sql.h>

enum MyEnum
{
	Rel,
	NonRel,
	cache
};

class DatabaseCon
{
public:
	DatabaseCon();
	~DatabaseCon();

	DatabaseCon(const DatabaseCon& rhs) = delete;
	DatabaseCon operator= (const DatabaseCon& rhs) = delete;

	//database types


	//functions to connect to different databases


private:

};

#endif // !DATABASECON_H
