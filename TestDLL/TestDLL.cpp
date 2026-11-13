// TestDLL.cpp : définit les fonctions exportées pour l'application DLL.
//

#include "stdafx.h"
#include "TestDLL.h"


// Il s'agit d'un exemple de variable exportée
TESTDLL_API int nTestDLL=0;

// Il s'agit d'un exemple de fonction exportée.
TESTDLL_API int fnTestDLL(void)
{
	return 42;
}

// Il s'agit du constructeur d'une classe qui a été exportée.
// consultez TestDLL.h pour la définition de la classe
CTestDLL::CTestDLL()
{
	return;
}
