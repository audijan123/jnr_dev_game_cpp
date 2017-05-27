#pragma once


namespace JGE
{
	class mainStateManager
	{
	public:
		mainStateManager();
		~mainStateManager();

		bool getRiftStatus() const				{ return bRiftStatus; };
		bool getRiftBrowserStatus() const		{ return bRiftBrowserStatus; };
		bool getHauptFensterStatus() const		{ return bHauptFensterStatus; };
		bool getTavernStatus() const			{ return bTavernStatus; };
		bool getProgrammStatus() const			{ return bRun; };
		bool getPauseStatus() const				{ return bPause; };
		bool getTavernHoverStatus()	const		{ return bTavernHoverStatus; };
		bool getPortalHoverStatus()	const		{ return bPortalHoverStatus; };
		bool getHimmelStatus() const			{ return bHimmel; };
		bool getTavernBankStatus() const		{ return bBankingStatus; };
		bool getbGoldVerändernStatus() const	{ return bGoldVerändern; };
		bool getItemShopStatus() const			{ return bItemShopStatus; };
		bool getItemShopCapMenuStatus() const	{ return bItemShopCapMenuStatus; };
		bool getItemShopBonusMenuStatus() const { return bItemShopBonusMenuStatus; };

		void setRiftStatus(const bool& status)				{ bRiftStatus = status; };
		void setRiftBrowserStatus(const bool& status)		{ bRiftBrowserStatus = status; };
		void setHauptFensterStatus(const bool& status)		{ bHauptFensterStatus = status; };
		void setTavernStatus(const bool& status)			{ bTavernStatus = status; };
		void setProgrammStatus(const bool& status)			{ bRun = status; };
		void setPauseStatus(const bool& status)				{ bPause = status; };
		void setTavernHoverStatus(const bool& status)		{ bTavernHoverStatus = status; };
		void setPortalHoverStatus(const bool& status)		{ bPortalHoverStatus = status; };
		void setHimmelStatus(const bool& status)			{ bHimmel = status; };
		void setTavernBankStatus(const bool& status)		{ bBankingStatus = status; };
		void setbGoldVerändernStatus(const bool& status)	{ bGoldVerändern = status; };
		void setItemShopStatus(const bool& status)			{ bItemShopStatus = status; };
		void setItemShopCapMenuStatus(const bool& status)	{ bItemShopCapMenuStatus = status; };
		void setItemShopBonusMenuStatus(const bool& status) { bItemShopBonusMenuStatus = status; };

	private:

		bool bRun;
		bool bRiftStatus;
		bool bRiftBrowserStatus;
		bool bHauptFensterStatus;
		bool bTavernStatus;
		bool bTavernHoverStatus = false;
		bool bPause = false;
		bool bPortalHoverStatus = false;
		bool bHimmel = true;
		bool bBankingStatus = false;
		bool bGoldVerändern = false;
		bool bItemShopStatus = false;
		bool bItemShopCapMenuStatus = false;
		bool bItemShopBonusMenuStatus = false;


	};


}