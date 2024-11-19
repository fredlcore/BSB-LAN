#!/usr/bin/env python

#----------------------------------------------------------------------------
# sample code to show how BSB-LAN's /D datalogs could be processed using
# pandas/python, including conversion to pivoted *.csv and some plot ideas
#----------------------------------------------------------------------------

from sys import argv
import pandas as pd

# -- read BSB-LAN /D logs into pandas dataframe:

if len(argv) > 1:
    # compile data from file names given on command line:
    df = pd.DataFrame()
    for fn in argv[1:]:
        print("Reading", fn, "...")
        df = pd.concat([df, pd.read_csv(fn, sep=";")])
else:
    print("Reading data from BSB-LAN ...")
    df = pd.read_csv("http://bsb-lan/D", sep=";")

print("Fitting data ...")

# make missing values digestible for pandas:
df.Value = pd.to_numeric(df.Value.replace("---", None))

# we want parameters without a trailing ".0":
df.Parameter = df.Parameter.astype("str").str.replace(".0", "", regex=False)

# convert Date values from string to datetime type:
df.Date = pd.to_datetime(df.Date, format="%d.%m.%Y %H:%M:%S", errors="coerce")

# drop duplicates, if any:
df = df.groupby(["Milliseconds", "Date"]).first().reset_index()

# pivot data for (much) easier access (this also drops the Milliseconds values):
df = df.pivot(
    index=["Date"], columns=["Parameter", "Description", "Unit"], values="Value"
).reset_index()

# flatten multi-index:
df.columns = [
    f"{c[0]}"
    + f'{f" - {c[1]}" if c[1] else ""}'
    + f'{f" [{c[2]}]" if c[2]==c[2] and c[2] else ""}'
    for c in df.columns.values
]

# you may want to save the processed data for faster re-loading later on:
# df.to_csv("BSB-LAN.csv", index=False)  # for compatibility with other programs
# df.to_pickle("BSB-LAN.pickle")  # to keep the Date column as datetime type

# show what data we have found:
print(df.info())
print(f"Found data from {df.Date.min()} to {df.Date.max()}")


# -- usage examples for data in pandas:

import matplotlib.pyplot as plt


def find_parameter_columns(df, parameter_name_contains):
    return [c for c in df.columns if str(parameter_name_contains) in c]


# graphically show statistics for numeric data fields found:
df.boxplot(showmeans=True, rot=90)
plt.tight_layout()
plt.show()

# plot of temperature parameters, similar to BSB-LAN's /DG:
# Date values will usually differ within each BSB-LAN sample set,
# as BSB-LAN most often cannot query multiple parameters within the same second.
# Therefore we fill the resulting "gaps" in our data, for uninterrupted plot lines:
df.fillna(method="ffill").plot(
    x="Date", y=find_parameter_columns(df, "°"), grid=True, figsize=(19.2, 10.8)
)
plt.tight_layout()
plt.show()


# - the following make sense mostly with data spanning multiple years:

import calendar

# infer detail columns from Date:
df["year"] = df.Date.dt.year
df["month"] = df.Date.dt.month
df["day"] = df.Date.dt.day
df["time"] = df.Date.dt.hour + (df.Date.dt.minute + df.Date.dt.second / 60) / 60

# plot flow temperature set point over outside temperature, by year:
outside_temperature_column = find_parameter_columns(df, 8700)[0]
# note: we're using heating circuit 2 (parameter 8774) here!:
flow_temperature_set_point_column = find_parameter_columns(df, 8774)[0]
for year in df.year.unique():
    dfx = df.query(f"year=={year}")
    plt.scatter(
        dfx[outside_temperature_column],
        dfx[flow_temperature_set_point_column],
        0.1,
        label=year,
    )
plt.xlabel(outside_temperature_column)
plt.ylabel(flow_temperature_set_point_column)
plt.legend(markerscale=9)
plt.grid()
plt.show()


# plot y over x, in a calendar format:
def calendar_plot(df, x, y):
    fig, ax = plt.subplots(
        4, 3, sharex=True, sharey=True, layout="constrained", figsize=(10, 10)
    )
    for month in range(1, 13):
        dfm = df.query(f"month=={month}")
        a = ax.flat[month - 1]
        for year in sorted(dfm.year.unique()):
            dfmy = dfm.query(f"year=={year}")
            a.scatter(dfmy[x], dfmy[y], 0.1, alpha=0.5, label=int(year))
        if len(dfm):
            a.set_title(calendar.month_name[month])
            a.grid()
            leg = a.legend(markerscale=9)
            for lh in leg.legendHandles:
                lh.set_alpha(1)
        else:
            a.set_frame_on(False)
            a.tick_params(bottom=False, left=False)
    plt.suptitle(f"{y} over {x}", fontweight="bold")
    plt.show()


calendar_plot(df, "time", outside_temperature_column)
calendar_plot(df, "day", outside_temperature_column)
