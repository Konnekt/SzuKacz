#pragma once
#include "IMController.h"

namespace SzuKacz
{
	class Controller : public IMController
	{
		public:
			/* Class version */
			STAMINA_OBJECT_CLASS_VERSION(Controller, IMController, Version(1,2,0,0));

		public:
			inline static Controller* getInstance()
			{
				if(!instance.isValid())
					instance = new Controller;
				return instance;
			}
			std::list<Result> findContact(int field, std::string &toMatch, int relationType, bool caseSensitive, bool fromList = 1, bool save = 0);
			void openSearchWindow();
			void quickSearchToolbarRefresh(bool move = 0);
			void quickSearchToolbarHide(bool focusRoster = 1);
			void selectCnt(HWND listView, int cnt);

		public:
			HWND searchWindow; //uchwyt okna
			HWND quickSearchToolbar; //uchwyt Toolbara z szybkim wyszukiwaniem
			HWND quickSearchEdit; //uchwyt Edita w szybkim wyszukiwaniu
			HWND konnektWindow; //uchwyt g³ównego okna K
			HWND konnektRoster; //uchwyt okna listy kontkatów
			WNDPROC konnektWindowOldProc; //stary proc g³ównego okna
			WNDPROC quickSearchToolbarOldProc; //stary proc toolbara szybkiego wyszukiwania
			WNDPROC quickSearchEditOldProc; //stary proc edita szybkiego wyszukiwania
			MRU* mruList; //obiekt do obs³ugi MRU
			std::list<SzuKacz::Result> searchResults; //wyniki wyszukiwania
			std::list<SzuKacz::Result> quickSearchResults; //wyniki szybkiego wyszukiwania
			std::list<SzuKacz::Result>::iterator* currentQuickSearchResult; //ostatni zaznaczony wynik
			bool quickSearchToolbarVisible; //czy toolbar szybkiego wyszukiwania jest ukryty
			bool quickSearchToolbarMoved; //czy toolbar szybkiego wyszukiwania jest przesuniêty

		protected:
			Controller();
			void onPrepare();
			void onAction();
			void onEnd();

		protected:
			static SharedPtr<Controller> instance;
	};
}