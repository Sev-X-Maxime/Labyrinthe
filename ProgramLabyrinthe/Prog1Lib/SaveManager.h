#pragma once
#pragma warning(disable : 4984)

#ifdef MYTOOL_EXPORTS
#define MYTOOL_API __declspec(dllexport)
#else
#define MYTOOL_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <type_traits>

#include "FileStream.h"
#include "DynamicArray.h"

using namespace std;

typedef ios_base ib;

namespace Tools
{
	class MYTOOL_API SaveManager
	{
		string path;
		string* encryptionKey;

	public:
		SaveManager(const string& _path);
		SaveManager(const string& _path, const string& _encryptionKey);
		~SaveManager();

		/// <summary>
		/// Sauvegarder une donn�e
		/// </summary>
		/// <typeparam name="T">Type de la donn�e</typeparam>
		/// <param name="_key">Cl�</param>
		/// <param name="_data">Valeur</param>
		template<typename T>
		void SaveData(const string& _key, const T& _data)
		{
			const string& _sData = _key + ":" + Convert<T, string>(_data) + "\n";
			FileStream _fs = GetStream(ios_base::in | ios_base::out);
			if (KeyExists(_key))
			{
				DynamicArray<int> _keyPos = GetKeyIndex(_key);
				_fs.RemoveLine(GetKeyIndex(_key)[1]);
			}
			FileStream _fW = GetStream(ios_base::in | ios_base::app);
			_fW.Write(_sData);
		}
		 
		/// <summary>
		/// Obtenir une donn�e � partir de sa cl�
		/// </summary>
		/// <typeparam name="T">Type de la donn�e</typeparam>
		/// <param name="_key">Cl�</param>
		/// <returns>Donn�e</returns>
		template<typename T>
		T GetData(const string& _key)
		{
			if (!KeyExists(_key)) throw exception("Key doesn't exist");
			
			FileStream _fs = GetStream(ios_base::in);
			string _lineValue = _fs.ReadLine(GetKeyIndex(_key)[1]);

			DynamicArray<string> _tokens = SplitString(_lineValue, ":");
			unsigned int _contentParts = _tokens.GetSize();
			string _totalContent = "";

			for (unsigned int _i = 1; _i < _contentParts; _i++)
			{
				_totalContent += string(_i > 1 ? ":" : "") + _tokens[_i];
			} // Tout �a au cas o� la cha�ne r�cup�r�e contient le symbole :
 
			return Convert<string, T>(_totalContent);
		}

		/// <summary>
		/// V�rifier si une cl� donn�e existe
		/// </summary>
		/// <param name="_key">string : cl�</param>
		/// <returns>bool : existe ?</returns>
		bool KeyExists(const string& _key) const;


	private:
		/// <summary>
		/// Cr�er le fichier
		/// </summary>
		void FileCreate() const;

		/// <summary>
		/// V�rifier si le fichier existe
		/// </summary>
		/// <returns>bool</returns>
		bool FileExists() const;

		/// <summary>
		/// Construire un FileStream
		/// </summary>
		/// <param name="_openmode">Mode d'�criture</param>
		/// <returns>FileStream</returns>
		FileStream GetStream(const int _openmode) const;

		/// <summary>
		/// R�cup�rer l'index de la cl� et la ligne sur laquelle elle se trouve
		/// </summary>
		/// <param name="_key">Cl�</param>
		/// <returns>DynamicArray<int> (0 : index | 1 : ligne) | -1 si non trouv�e</returns>
		DynamicArray<int> GetKeyIndex(const string& _key) const;
		
		/// <summary>
		/// M�thode pour recr�er le split d'un string
		/// </summary>
		/// <param name="_text">string : � split</param>
		/// <param name="_separator">char : sur quoi split</param>
		/// <returns>vector : tableau de string</returns>
		DynamicArray<string> SplitString(const string& _text, const char* _separator) const;

		/// <summary>
		/// Convertisseur entre types
		/// </summary>
		/// <typeparam name="Input">Type d'entr�e</typeparam>
		/// <typeparam name="Result">Type de sortie attendu</typeparam>
		/// <param name="_input">Valeur</param>
		/// <returns>Valeur en type attendu</returns>
		template<typename Input, typename Result>
		Result Convert(const Input& _input) const // "constexpr" sert � dire au compilateur qu'il doit analyser les chemins (les if), sinon il dit qu'il y'a une erreur car ce con pense
		{											// que t'essayes de convertir des types en de la merde. 

			if constexpr (is_same<Input, Result>::value) return _input;

			if constexpr (is_same<Input, string>::value) // Si la valeur d'entr�e est un string
			{
				if constexpr (is_same<Result, int>::value) return std::stoi(_input);
				else if constexpr (is_same<Result, bool>::value) return (_input == "true\r");
				else if constexpr (is_same<Result, char>::value) return _input[0];
			}
			else if constexpr (is_same<Input, int>::value) return to_string(_input);
			else if constexpr (is_same<Input, bool>::value) return (_input ? "true" : "false");
			else if constexpr (is_same<Input, char>::value) return _input[0];

			throw exception("Unable to convert type");
		}

	};
}




