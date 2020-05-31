/* XMRig
 * Copyright 2018-2020 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2020 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef XMRIG_ETHSTRATUMCLIENT_H
#define XMRIG_ETHSTRATUMCLIENT_H


#include "base/net/stratum/Client.h"


namespace xmrig {


class IClientListener;


class EthStratumClient : public Client
{
public:
    XMRIG_DISABLE_COPY_MOVE_DEFAULT(EthStratumClient)

    EthStratumClient(int id, const char *agent, IClientListener *listener);

protected:

protected:
    int64_t submit(const JobResult &result) override;
    void login() override;
    void onClose() override;

    bool handleResponse(int64_t id, const rapidjson::Value &result, const rapidjson::Value &error) override;
    void parseNotification(const char *method, const rapidjson::Value &params, const rapidjson::Value &error) override;

private:
    const char *errorMessage(const rapidjson::Value &error) const;
    uint64_t extraNonce(const rapidjson::Value &result) const;
    uint64_t target(const rapidjson::Value &params) const;
    void authorize();
    void onAuthorizeResponse(const rapidjson::Value &result, bool success, uint64_t elapsed);
    void onSubscribeResponse(const rapidjson::Value &result, bool success, uint64_t elapsed);
    void setTarget(const rapidjson::Value &params);
    void subscribe();

    bool m_authorized       = false;
    uint64_t m_target       = 0;
    uint64_t m_extraNonce   = 0;
};


} /* namespace xmrig */


#endif /* XMRIG_ETHSTRATUMCLIENT_H */