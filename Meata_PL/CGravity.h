#pragma once

class CObject;

class CGravity
{
public:
	CGravity();
	~CGravity();

private:
	CObject* m_pOwner;

	bool m_bGround;

public:
	void SetGround(bool _b);
public:


	void finalupdate();


	friend class CObject;
};

