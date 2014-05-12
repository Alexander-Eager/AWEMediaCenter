// header file
#include "JsonPath.h"

// debug
#include "debug_macros/debug.h"
#include <iostream>

using namespace Json;
using namespace std;
using namespace AWE;

JsonKey::JsonKey(uint key)
	:	myIsString(false),
		myIsIndex(true),
		myInteger(key)
	{ }

JsonKey::JsonKey(int key)
	:	JsonKey((uint) key)
	{ }

JsonKey::JsonKey(QString key)
	:	myIsString(true),
		myString(key)
{
	key.toUInt(&myIsIndex);
}

JsonKey::JsonKey(const char key[])
	:	JsonKey(QString(key))
	{ }

JsonKey::JsonKey(const string& key)
	:	JsonKey(QString::fromStdString(key))
	{ }

JsonKey& JsonKey::operator= (const JsonKey& other)
{
	myIsString = other.isString();
	myIsIndex = other.isArrayIndex();
	if (isString())
	{
		myString = other.toString();
	}
	else
	{
		myInteger = other.toInteger();
	}
	return *this;
}

JsonKey::~JsonKey() { }

JsonKey::JsonKey(const JsonKey& other)
	:	myIsString(other.myIsString),
		myIsIndex(other.myIsIndex)
{
	if (isString())
	{
		myString = other.toString();
	}
	else
	{
		myInteger = other.toInteger();
	}
}

bool JsonKey::isObjectKey() const
{
	return myIsString;
}

string JsonKey::toObjectKey() const
{
	if (!isObjectKey())
	{
		return "";
	}
	return myString.toStdString();
}

bool JsonKey::isArrayIndex() const
{
	return myIsIndex;
}

uint JsonKey::toArrayIndex() const
{
	if (!isArrayIndex())
	{
		return (uint) -1;
	}
	if (isString())
	{
		return myString.toUInt();
	}
	return myInteger;
}

bool JsonKey::isString() const
{
	return myIsString;
}

QString JsonKey::toString() const
{
	if (!isString())
	{
		return QString();
	}
	return myString;
}

bool JsonKey::isInteger() const
{
	return !myIsString;
}

uint JsonKey::toInteger() const
{
	if (!isInteger())
	{
		return (uint) -1;
	}
	return myInteger;
}

Value JsonPath::null = Value::null;

JsonPath::JsonPath(std::initializer_list<JsonKey> keys)
	:	myPath(keys)
	{ }

JsonPath::JsonPath(QString keys)
	:	JsonPath(keys.split('.'))
	{ }

JsonPath::JsonPath(const char keys[])
	:	JsonPath(QString(keys))
	{ }

JsonPath::JsonPath(QStringList keys)
{
	for (auto i : keys)
	{
		myPath.append(i);
	}
}

JsonPath::JsonPath(const JsonPath& other)
	:	myPath(other.myPath)
	{ }

const Value& JsonPath::followConst(const Value& data) const
{
	const Value* val = &data;
	for (auto key : myPath)
	{
		if (val->isObject() && key.isObjectKey())
		{
			string temp = key.toObjectKey();
			if (val->isMember(temp))
			{
				val = &( val->operator[] (temp) );
			}
			else
			{
				DEBUG_ERR("ERROR: Path does not exist")
				return null;
			}
		}
		else if (val->isArray() && key.isArrayIndex())
		{
			uint temp = key.toArrayIndex();
			if (temp < val->size())
			{
				val = &( val->operator[] (temp) );
			}
			else
			{
				DEBUG_ERR("ERROR: Path does not exist")
				return null;
			}
		}
		else
		{
			DEBUG_ERR("ERROR: Wrong value type for following path")
			return null;
		}
	}
	return *val;
}

Value& JsonPath::follow(Value& data) const
{
	Value* val = &data;
	for (auto key : myPath)
	{
		if (val->isObject() && key.isObjectKey())
		{
			string temp = key.toObjectKey();
			if (val->isMember(temp))
			{
				val = &( val->operator[] (temp) );
			}
			else
			{
				DEBUG_ERR("ERROR: Path does not exist")
				return null;
			}
		}
		else if (val->isArray() && key.isArrayIndex())
		{
			uint temp = key.toArrayIndex();
			if (temp < val->size())
			{
				val = &( val->operator[] (temp) );
			}
			else
			{
				DEBUG_ERR("ERROR: Path does not exist")
				return null;
			}
		}
		else
		{
			DEBUG_ERR("ERROR: Wrong value type for following path")
			return null;
		}
	}
	return *val;
}

Value& JsonPath::create(Value& data) const
{
	Value* val = &data;
	for (auto key : myPath)
	{
		if (val->isArray() && key.isArrayIndex())
		{
			val = &( val->operator[] (key.toArrayIndex()) );
		}
		else if (val->isObject() && key.isObjectKey())
		{
			val = &( val->operator[] (key.toObjectKey()) );
		}
		else
		{
			DEBUG_ERR("ERROR: Wrong value type for path creation")
		}
	}
	return *val;
}