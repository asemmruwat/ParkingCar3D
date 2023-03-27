import React, { useState } from 'react';
import { StyleSheet, View, FlatList, Alert, TouchableWithoutFeedback, Keyboard } from 'react-native';
import Header from './header';
import TodoItem from './todoItem';



export default function HomeList() {
  const [todos, setTodos] = useState([
    { text: 'buy coffee', key: '1' },
    { text: 'create an app', key: '2' },
    { text: 'play on the switch', key: '3' },
    { text: 'play on the switch', key: '4' },
    { text: 'play on the switch', key: '5' },
    { text: 'play on the switch', key: '6' },
    { text: 'create an app', key: '7' },
    { text: 'play on the switch', key: '8' },
    { text: 'play on the switch', key: '9' },
    { text: 'play on the switch', key: '10' },
    { text: 'play on the switch', key: '11' },
  ]);

  const pressHandler = (key) => {
    setTodos(prevTodos => {
      return prevTodos.filter(todo => todo.key != key);
    });
  };

  const submitHandler = (text) => {
    if (text.length > 3) {
      setTodos(prevTodos => {
        return [
          { text, key: Math.random().toString() },
          ...prevTodos
        ];
      });
    } else {
      Alert.alert('OOPS', 'Todo must be over 3 characters long', [
        { text: 'Understood', onPress: () => console.log('alert closed') }
      ]);
    }
  };

  return (

    <TouchableWithoutFeedback onPress={() => {
      Keyboard.dismiss();
      console.log('dismissed');
    }}>
    
       
        <View style={styles.list}>
        <Header />
          <FlatList
            showsHorizontalScrollIndicator={false}
            showsVerticalScrollIndicator={false}
            data={todos}
            renderItem={({ item }) => (
              <TodoItem item={item} pressHandler={pressHandler}/>
            )}
          />
        </View>
      
    </TouchableWithoutFeedback>
  );
}

const styles = StyleSheet.create({

  list: {
    marginTop:0,
    backgroundColor: '#FFFFFF',
    flex: 1,
  },
});
