/**
 * * * * * * * * * * * * * * * * * * * *
 * Copyright (C) 5/Dec/17 Carlos Brito *
 * * * * * * * * * * * * * * * * * * * *
 * 
 * @file
 */

#include <vector>
#include <list>
#include <mysql_devapi.h>
#include <boost/variant.hpp>
#include <mysql_xapi.h>

#include "ReadingFetcher.hpp"
#include "ReadRequest.hpp"

#include "srv/service/common.hpp"

using namespace std;

namespace celeste
{
namespace resource
{   
    // --- TYPE ABBREVIATIONS --------
    using value_type = ReadingFetcher::value_type;

    // --- LastReadRequest fetch implementations ---------
    template <>
    value_type ReadingFetcher::fetch_impl(mysqlx::Session&& dbSession,
                                           const LastReadRequest& req) const
    {
        auto res = dbSession.sql(
                    R"(
                    SELECT a.sf, a.t, a.data FROM PointRecord a
                    INNER JOIN (
                    SELECT
                    Point_id,
                    Model_id,
                    Device_id,
                    Model_idx,
                    max(DeviceRecord_idx) DeviceRecord_idx,
                    max(idx) idx
                    FROM PointRecord
                    WHERE Point_id    = ?
                    AND Model_id      = ?
                    AND Device_id     = ?
                    GROUP BY Point_id, Model_id, Device_id, Model_idx) b
                    ON a.Point_id = b.Point_id AND
                    a.Model_id = b.Model_id AND
                    a.Device_id = b.Device_id AND
                    a.Model_idx = b.Model_idx AND
                    a.idx = b.idx AND
                    a.DeviceRecord_idx = b.DeviceRecord_idx
                    ;
                    )" // end literal
                    ).bind(ValueList{
                        req.PointId.c_str(),
                        req.ModelId.c_str(),
                        req.DeviceId
                    }).execute();

        if (res.count() > 0)
        {
            mysqlx::SerializableRow row = res.fetchOne();
            return row.as<Reading<mysqlx::EnhancedValue>>();
        } else
        { 
            return Reading<mysqlx::EnhancedValue>{};
        }
    }

    // --- RangeReadRequest fetch implementations --------
    template <>
    std::vector<value_type> ReadingFetcher::fetch_impl(mysqlx::Session&& dbSession,
                                                       const RangeReadRequest& req) const
    {
        auto res = dbSession.sql(
                    R"(
                    SELECT a.sf, a.t, a.data FROM PointRecord a
                    WHERE
                    Device_id = ? 
                    AND Model_id = ?
                    AND Point_id = ?
                    AND t > ?
                    AND t < ?
                    ;
                    )" // end literal
                    ).bind(ValueList{
                        req.DeviceId,
                        req.ModelId.c_str(),
                        req.PointId.c_str(),
                        req.start.c_str(),
                        req.end.c_str()
                    }).execute();

        if (res.count() > 0)
        {   
            std::vector<value_type> readings(res.count());
            int i = 0;
            for (auto&& r : res.fetchAll())
                readings[i++] = static_cast<mysqlx::SerializableRow>(move(r)).as<value_type>();
            return readings;
        } else
        {
            return std::vector<value_type>{};
        }
    }

    // --- YesterdayReadRequest fetch implementations ----

    // --- TodayReadRequest fetch implementations --------
}
}