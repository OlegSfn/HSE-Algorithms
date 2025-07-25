import streamlit as st
import pandas as pd
import plotly.express as px
import os


def main():
    st.set_page_config(layout="wide")

    file_directory = '.'
    filetype = '.txt'
    txt_files = [f for f in os.listdir(file_directory) if f.endswith(filetype)]

    if txt_files:
        combined_range_data = pd.DataFrame()
        combined_reversed_data = pd.DataFrame()
        combined_almost_sorted_data = pd.DataFrame()

        for filename in txt_files:
            try:
                file_path = os.path.join(file_directory, filename)

                df = pd.read_csv(file_path, header=None)

                array_sizes = df.iloc[0].dropna().astype(float).values
                range_times = df.iloc[1].dropna().astype(float).values
                reversed_times = df.iloc[2].dropna().astype(float).values
                almost_sorted_times = df.iloc[3].dropna().astype(float).values

                if not (
                    len(array_sizes) == len(range_times) == len(reversed_times) == len(almost_sorted_times)
                ):
                    st.error(f"Ошибка: массивы в файле {file_path} должны быть одинаковой длины.")
                    continue

                df_range = pd.DataFrame({
                    'Размер массива': array_sizes,
                    f'Range Arrays ({file_path})': range_times
                })

                df_reversed = pd.DataFrame({
                    'Размер массива': array_sizes,
                    f'Reversed Arrays ({file_path})': reversed_times
                })

                df_almost_sorted = pd.DataFrame({
                    'Размер массива': array_sizes,
                    f'Almost Sorted Arrays ({file_path})': almost_sorted_times
                })

                combined_range_data = pd.merge(
                    combined_range_data, df_range, on='Размер массива', how='outer'
                ) if not combined_range_data.empty else df_range

                combined_reversed_data = pd.merge(
                    combined_reversed_data, df_reversed, on='Размер массива', how='outer'
                ) if not combined_reversed_data.empty else df_reversed

                combined_almost_sorted_data = pd.merge(
                    combined_almost_sorted_data, df_almost_sorted, on='Размер массива', how='outer'
                ) if not combined_almost_sorted_data.empty else df_almost_sorted

            except Exception as e:
                st.error(f"Ошибка при обработке файла {file_path}: {e}")

        if not combined_range_data.empty:
            combined_range_data = combined_range_data.sort_values('Размер массива')
            fig_range = px.line(
                combined_range_data, x='Размер массива', y=combined_range_data.columns[1:],
                title='Количество сравнений для случайных массивов', markers=False
            )
            fig_range.update_layout(hovermode='x unified')

        if not combined_reversed_data.empty:
            combined_reversed_data = combined_reversed_data.sort_values('Размер массива')
            fig_reversed = px.line(
                combined_reversed_data, x='Размер массива', y=combined_reversed_data.columns[1:],
                title='Количество сравнений для отсортированных в обратном порядке массивов', markers=False
            )
            fig_reversed.update_layout(hovermode='x unified')

        if not combined_almost_sorted_data.empty:
            combined_almost_sorted_data = combined_almost_sorted_data.sort_values('Размер массива')
            fig_almost_sorted = px.line(
                combined_almost_sorted_data, x='Размер массива',y=combined_almost_sorted_data.columns[1:],
                title='Количество сравнений для почти отсортированных массивов', markers=False
            )
            fig_almost_sorted.update_layout(hovermode='x unified')

        st.markdown("## Сравнение количества посимвольных сравнений для разных типов массивов")

        if not combined_range_data.empty:
            fig_range.update_yaxes(title_text="Количество сравнений")
            st.plotly_chart(fig_range, use_container_width=True)

        if not combined_reversed_data.empty:
            fig_reversed.update_yaxes(title_text="Количество сравнений")
            st.plotly_chart(fig_reversed, use_container_width=True)

        if not combined_almost_sorted_data.empty:
            fig_almost_sorted.update_yaxes(title_text="Количество сравнений")
            st.plotly_chart(fig_almost_sorted, use_container_width=True)

if __name__ == "__main__":
    main()