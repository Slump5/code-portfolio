// Author: Thomas Hoerger
// Thomas Hoerger - Copyright © 2025 SkyView Weather App Final Build
// Solo Group 9
// 4-24-2025
// Description: Select and display data from any database table using dropdown picker and restored flat list layout.

import React, { useState, useEffect } from 'react';
import { View, Text, FlatList, StyleSheet, ActivityIndicator, Pressable } from 'react-native';
import DropDownPicker from 'react-native-dropdown-picker';

export default function DisplayScreen() {
  const [tab, setTab] = useState('Display'); // current tab
  const [tables, setTables] = useState([]); // available table names
  const [selectedTable, setSelectedTable] = useState(''); // current table
  const [data, setData] = useState([]); // rows from table
  const [loading, setLoading] = useState(false); // loading state

  // dropdown state
  const [open, setOpen] = useState(false);
  const [items, setItems] = useState([]); // dropdown options

  // Load table names
  const fetchTables = async () => {
    try {
      const res = await fetch('http://34.123.143.201/get_table_list.php');
      const json = await res.json();
      setTables(json);
      setItems(json.map(tbl => ({ label: tbl, value: tbl })));
      setSelectedTable(json[0]);
    } catch (err) {
      console.error('Failed to load table list:', err);
    }
  };

  // Load data from selected table
  const fetchData = async () => {
    if (!selectedTable) return;
    try {
      setLoading(true);
      const res = await fetch(`http://34.123.143.201/get_table_data.php?table=${selectedTable}`);
      const json = await res.json();
      if (json.rows) setData(json.rows);
    } catch (err) {
      console.error('Data fetch failed:', err);
    } finally {
      setLoading(false);
    }
  };

  // On component mount: get tables
  useEffect(() => {
    fetchTables();
  }, []);

  // On table change or tab switch to "Display": load data
  useEffect(() => {
    if (tab === 'Display' && selectedTable) {
      fetchData();
    }
  }, [tab, selectedTable]);

  return (
    <View style={styles.container}>
      {/* Tab bar to switch between views */}
      <View style={styles.tabContainer}>
        <Pressable onPress={() => setTab('Select')}>
          <Text style={[styles.tab, tab === 'Select' && styles.activeTab]}>Select</Text>
        </Pressable>
        <Pressable onPress={() => setTab('Display')}>
          <Text style={[styles.tab, tab === 'Display' && styles.activeTab]}>Display</Text>
        </Pressable>
      </View>

      {/* Table selector dropdown */}
      {tab === 'Select' && (
        <View style={styles.dropdownWrapper}>
          <Text style={styles.label}>Choose a table:</Text>
          <DropDownPicker
            open={open}
            setOpen={setOpen}
            items={items}
            setItems={setItems}
            value={selectedTable}
            setValue={setSelectedTable}
            placeholder="Select a table"
            style={styles.dropdown}
            dropDownContainerStyle={styles.dropdownBox}
          />
        </View>
      )}

      {/* Display fetched rows */}
      {tab === 'Display' && (
        <>
          <Text style={styles.selected}>Showing: {selectedTable}</Text>
          {loading ? (
            <ActivityIndicator size="large" color="#007AFF" />
          ) : (
            <FlatList
              data={data}
              keyExtractor={(item, index) => index.toString()}
              contentContainerStyle={styles.list}
              renderItem={({ item }) => (
                <View style={styles.row}>
                  {Object.entries(item).map(([key, value]) => (
                    <Text key={key} style={styles.item}>
                      <Text style={styles.bold}>{key}:</Text> {String(value)}
                    </Text>
                  ))}
                </View>
              )}
              ListEmptyComponent={<Text style={styles.empty}>No data found.</Text>}
            />
          )}
        </>
      )}
    </View>
  );
}

// Styles
const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingTop: 40,
    paddingHorizontal: 16,
    backgroundColor: '#fff',
  },
  tabContainer: {
    flexDirection: 'row',
    justifyContent: 'center',
    marginBottom: 16,
  },
  tab: {
    fontSize: 16,
    padding: 10,
    marginHorizontal: 12,
    color: '#444',
  },
  activeTab: {
    borderBottomWidth: 2,
    borderColor: '#007AFF',
    fontWeight: 'bold',
    color: '#007AFF',
  },
  dropdownWrapper: {
    marginTop: 20,
    zIndex: 999,
  },
  label: {
    fontSize: 18,
    marginBottom: 10,
    textAlign: 'center',
  },
  dropdown: {
    backgroundColor: '#f1f1f1',
  },
  dropdownBox: {
    backgroundColor: '#f1f1f1',
    zIndex: 999,
  },
  selected: {
    fontSize: 16,
    marginBottom: 10,
    textAlign: 'center',
  },
  list: {
    paddingBottom: 100,
  },
  row: {
    backgroundColor: '#f5f5f5',
    marginBottom: 10,
    padding: 10,
    borderRadius: 8,
  },
  item: {
    fontSize: 14,
    marginBottom: 4,
  },
  bold: {
    fontWeight: 'bold',
  },
  empty: {
    textAlign: 'center',
    fontStyle: 'italic',
    marginTop: 20,
    color: '#888',
  },
});

