#include "Menu.hpp"

namespace Menu {
    void RenderMenu() {
        std::string windowTitle = "PG3D WebSocket Mod - ";
        windowTitle += Variables::WebSocket::m_strSocketStatus;

        ImGui::Begin(windowTitle.c_str());
        {
            ImGui::Text("Command: %s", Variables::WebSocket::m_strCommandStatus.c_str());
            ImGui::Separator();

            static const char* currencyTypes[] = {
                "GemsCurrency", "Coins", "ClanSilver", "ClanLootBoxPoints",
                "Coupons", "PixelPassCurrency", "RouletteAdsCurrency",
                "RouletteAdsSpin", "PixelBucks", "BattlePassCurrency",
                "CurrencyCompetitionTier1", "CurrencyCompetitionTier2", "EventCurrency"
            };
            static int currentCurrency = 0;

            if (Variables::Account::m_strCurrency != currencyTypes[currentCurrency]) {
                for (int i = 0; i < IM_ARRAYSIZE(currencyTypes); i++) {
                    if (Variables::Account::m_strCurrency == currencyTypes[i]) {
                        currentCurrency = i;
                        break;
                    }
                }
            }

            if (ImGui::Combo("Currency", &currentCurrency, currencyTypes, IM_ARRAYSIZE(currencyTypes))) {
                Variables::Account::m_strCurrency = currencyTypes[currentCurrency];
            }

            ImGui::InputInt("Amount", &Variables::Account::m_iCurrencyAmount);
            //            ImGui::InputInt("Cause", &Variables::Account::m_iCurrencyCause);

            if (ImGui::Button("Add Currency")) {
                Variables::WebSocket::m_strCommandStatus = "-";
                Variables::Account::m_bAddCurrency = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Manual Reload")) Variables::WebSocket::m_bReloadSocket = true;
        }
        ImGui::End();
    }
}