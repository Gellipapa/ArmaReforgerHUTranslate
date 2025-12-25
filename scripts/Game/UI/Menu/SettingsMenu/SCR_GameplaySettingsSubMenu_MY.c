modded class SCR_GameplaySettingsSubMenu
{
	protected static ref array<string> s_aLanguagesHU = {
		"en_us",
		"fr_fr",
		"it_it",
		"de_de",
		"es_es",
		"cs_cz",
		"pl_pl",
		"ru_ru",
		"ja_jp",
		"ko_kr",
		"pt_br",
		"zh_cn",
		"hu_hu",
		"uk_ua",
	};
	
	override protected void BindLanguage()
	{
		BaseContainer setting = GetGame().GetEngineUserSettings().GetModule(m_sUserInterfaceSettings);
		if (!setting)
			return;

		string currentLang;
		setting.Get("LanguageCode", currentLang);

		int i = s_aLanguagesHU.Find(currentLang);
		if (i == -1)
			i = 0;

		Widget w = m_wRoot.FindAnyWidget("Language");
		if (!w)
			return;

		SCR_SpinBoxComponent comp = SCR_SpinBoxComponent.Cast(w.FindHandler(SCR_SpinBoxComponent));
		if (!comp)
			return;

		comp.SetCurrentItem(i);
		comp.m_OnChanged.Remove(OnLanguageChange);
		comp.m_OnChanged.Insert(OnLanguageChange);
	}

	override protected void OnLanguageChange(SCR_SpinBoxComponent comp, int i)
	{
		BaseContainer setting = GetGame().GetEngineUserSettings().GetModule(m_sUserInterfaceSettings);
		if (!setting)
			return;

		if (!s_aLanguagesHU.IsIndexValid(i))
			return;

		const string settingName = "LanguageCode";
		setting.Set(settingName, s_aLanguagesHU[i]);
		GetGame().UserSettingsChanged();

		m_OnLanguageChanged.Invoke(this);
		SCR_AnalyticsApplication.GetInstance().ChangeSetting(m_sUserInterfaceSettings, settingName);
	}
}
