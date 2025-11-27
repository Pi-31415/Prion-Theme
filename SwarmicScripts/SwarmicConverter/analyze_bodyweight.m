function analyze_bodyweight()
    % Analyze moving average and trend projection for bodyweight data
    % File: bodyweight_entries.csv must be in the current working directory

    %% ---------------------- Load and prepare data ---------------------- %%
    filename = 'bodyweight_entries.csv';

    % Import options, force log_date as datetime
    opts = detectImportOptions(filename, 'NumHeaderLines', 0);
    % Ensure the key variables are imported correctly
    if any(strcmp(opts.VariableNames, 'log_date'))
        opts = setvartype(opts, 'log_date', 'datetime');
        opts = setvaropts(opts, 'log_date', 'InputFormat', 'yyyy-MM-dd');
    end

    T = readtable(filename, opts);

    % Basic checks
    requiredVars = {'log_date', 'weight_kg'};
    for k = 1:numel(requiredVars)
        if ~ismember(requiredVars{k}, T.Properties.VariableNames)
            error('Required column "%s" not found in CSV.', requiredVars{k});
        end
    end

    % Sort by date in case rows are out of order
    T = sortrows(T, 'log_date');

    % Remove rows with missing key values
    T = rmmissing(T, 'DataVariables', {'log_date','weight_kg'});

    if height(T) < 2
        error('Not enough data points after cleaning to perform analysis.');
    end

    %% ---------------------- Moving average analysis -------------------- %%
    % Choose moving window length in days (configurable)
    windowDays = 7;                % 7-day time window
    win = days(windowDays);

    % Compute time-based moving average using log_date as sample points
    T.mavg_weight_kg = movmean(T.weight_kg, win, 'SamplePoints', T.log_date);

    %% ---------------------- Trend from 2025-10-10 ---------------------- %%
    % Start date for trend fitting
    trendStart = datetime(2025,10,10);     % 10 Oct 2025

    % Logical index for dates >= trendStart
    idxTrend = T.log_date >= trendStart;

    % Extract subset for trend (if any)
    Ttrend = T(idxTrend, :);

    if height(Ttrend) >= 2
        % Convert dates to numeric "days since first trend date"
        t0 = Ttrend.log_date(1);
        x = days(Ttrend.log_date - t0);        % predictor (numeric time)
        y = Ttrend.weight_kg;                  % response (weight)

        % Fit linear trend: y = p(1)*x + p(2)
        p = polyfit(x, y, 1);

        % Target prediction date (September 2026)
        targetDate = datetime(2026, 9, 1);     % 1 Sep 2026 (adjust if desired)
        xTarget = days(targetDate - t0);
        predictedWeight = polyval(p, xTarget);

        hasTrend = true;
    else
        % Not enough data after 10 Oct 2025 to fit a trend
        hasTrend = false;
        targetDate = datetime(2026, 9, 1);     %#ok<NASGU>  % still defined for consistency
        predictedWeight = NaN;
    end

    %% ---------------------- Plotting results --------------------------- %%
    figure('Name','Bodyweight Analysis','NumberTitle','off');
    tiledlayout(2,1);

    % ---- Plot 1: Original data and moving average ----
    nexttile;
    hold on;
    plot(T.log_date, T.weight_kg, 'o-', 'DisplayName', 'Daily weight');
    plot(T.log_date, T.mavg_weight_kg, '-', 'LineWidth', 1.5, ...
         'DisplayName', sprintf('%d-day moving average', windowDays));
    hold off;
    grid on;
    xlabel('Date');
    ylabel('Weight (kg)');
    title(sprintf('Bodyweight and %d-day Moving Average', windowDays));
    legend('Location','best');

    % ---- Plot 2: Trend fit and forecast (if available) ----
    nexttile;
    hold on;
    plot(T.log_date, T.weight_kg, 'o', 'DisplayName', 'All data');

    if hasTrend
        % Trend subset
        plot(Ttrend.log_date, Ttrend.weight_kg, 's', 'DisplayName', ...
             sprintf('Data from %s onward', datestr(trendStart)));

        % Build line from min trend date to target
        xLine = linspace(min(x), xTarget, 100);
        tLine = t0 + days(xLine);
        yLine = polyval(p, xLine);

        plot(tLine, yLine, '-', 'LineWidth', 1.5, 'DisplayName', 'Linear trend');

        % Mark forecast point
        plot(targetDate, predictedWeight, 'rx', 'MarkerSize', 10, ...
             'LineWidth', 2, 'DisplayName', sprintf('Forecast %s', datestr(targetDate)));

        legend('Location','best');
        title('Trend and Forecast from 10-Oct-2025 Onward');
    else
        title('Trend and Forecast: not enough data from 10-Oct-2025 onward');
        legend('Location','best');
    end

    grid on;
    xlabel('Date');
    ylabel('Weight (kg)');
    hold off;

    %% ---------------------- Command window output ---------------------- %%
    fprintf('Total records used: %d\n', height(T));
    fprintf('Moving average window: %d calendar days.\n', windowDays);

    if hasTrend
        fprintf('Trend start date: %s\n', datestr(trendStart));
        fprintf('Target prediction date: %s\n', datestr(targetDate));
        fprintf('Predicted weight on %s: %.2f kg\n', datestr(targetDate), predictedWeight);
        fprintf('Trend slope: %.4f kg/day (positive = gaining, negative = losing)\n', p(1));
    else
        fprintf(['Not enough data on or after %s to fit a trend.\n' ...
                 'At least 2 entries on or after this date are required.\n'], ...
                 datestr(trendStart));
    end
end
