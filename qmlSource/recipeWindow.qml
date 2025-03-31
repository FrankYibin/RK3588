/**********************************************************************************************************

      Copyright (c) Branson Ultrasonics Corporation, 1996-2021

     This program is the property of Branson Ultrasonics Corporation
     Copying of this software is expressly forbidden, without the prior
     written consent of Branson Ultrasonics Corporation.

 ---------------------------- MODULE DESCRIPTION ----------------------------
 
 xxxxx
 
 **********************************************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQml.Models 2.15
import Style 1.0
import Com.Branson.UIScreenEnum 1.0
import Com.Branson.RecipeEnum 1.0
Item {
    id: recipeCardWindowItem
    readonly property int qmlscreenIndicator:  UIScreenEnum.RECIPES

    property string qmltextMenuName:                qsTr("Recipes")
    property string qmltextTabBarRecipe:            qsTr("Recipes")
    property string qmltextTabBarSequence:          qsTr("Sequence")
    property string qmltextNewRecipe:               qsTr("New Recipe")
    property string qmltextNewSequence:             qsTr("New Sequence")
    property string qmltextActions:                 qsTr("Actions")
    property string qmltextProductionRun:           qsTr("PRODUCTION RUN")
    property string qmltextEditRecipe:              qsTr("EDIT RECIPE")
    property string qmltextEditSequence:            qsTr("EDIT SEQUENCE")
    property string qmltextResetCycleCount:         qsTr("RESET CYCLE COUNT")
    property string qmltextSetAsActive:             qsTr("SET AS ACTIVE")
    property string qmltextCycleCount:              qsTr("Cycle Count")
    property string qmltextSequenceCount:           qsTr("Sequence Count")


    property var qmlTextArray: [qmltextTabBarRecipe, qmltextTabBarSequence,
                                qmltextNewRecipe, qmltextNewSequence,
                                qmltextActions, qmltextProductionRun, qmltextEditRecipe,
                                qmltextEditSequence, qmltextResetCycleCount, qmltextSetAsActive,
                                qmltextCycleCount, qmltextSequenceCount
                                ]

    function updateLanguage()
    {
        qmlTextArray = languageConfig.getLanguageStringList(UIScreenEnum.RECIPES, qmlTextArray)
        qmltextTabBarRecipe         = qmlTextArray[textEnum.recipeTabIdx]
        qmltextTabBarSequence       = qmlTextArray[textEnum.sequenceTabIdx]
        qmltextNewRecipe            = qmlTextArray[textEnum.newRecipeIdx]
        qmltextNewSequence          = qmlTextArray[textEnum.newSequenceIdx]
        qmltextActions              = qmlTextArray[textEnum.actionIdx]
        qmltextProductionRun        = qmlTextArray[textEnum.productionRunIdx]
        qmltextEditRecipe           = qmlTextArray[textEnum.editRecipeIdx]
        qmltextEditSequence         = qmlTextArray[textEnum.editSequenceIdx]
        qmltextResetCycleCount      = qmlTextArray[textEnum.resetCycleCountIdx]
        qmltextSetAsActive          = qmlTextArray[textEnum.setAsActiveIdx]
        qmltextCycleCount           = qmlTextArray[textEnum.recipeCycleCountIdx]
        qmltextSequenceCount        = qmlTextArray[textEnum.sequenceCountIdx]
        qmltextMenuName = languageConfig.getLanguageMenuName(UIScreenEnum.RECIPES, qmltextMenuName)
        recipeTabBar.currentIndex = 0
        recipeActionModel.resetModel()
        sequenceActionModel.resetModel()

    }

    Connections {
        target: mainWindow
        function onSignalCurrentLanguageChanged()
        {
            updateLanguage()
        }
    }

    Component.onCompleted: {
        sequenceDataModel.resetModel()
        recipeModel.loadRecipeCards()
        updateLanguage()
        mainWindow.setHeaderTitle(qmltextMenuName, UIScreenEnum.RECIPES)
    }

    QtObject {
        id: textEnum
        readonly property int recipeTabIdx:             0
        readonly property int sequenceTabIdx:           1
        readonly property int newRecipeIdx:             2
        readonly property int newSequenceIdx:           3
        readonly property int actionIdx:                4
        readonly property int productionRunIdx:         5
        readonly property int editRecipeIdx:            6
        readonly property int editSequenceIdx:          7
        readonly property int resetCycleCountIdx:       8
        readonly property int setAsActiveIdx:           9
        readonly property int recipeCycleCountIdx:      10
        readonly property int sequenceCountIdx:         11
    }

    ListModel {
        id: recipeActionModel
        function resetModel()
        {
            recipeActionModel.clear()
            recipeActionModel.append({"ActionName":      qmltextProductionRun,
                                 "ActionIndex":     RecipeEnum.PRODUCTION_RUN_IDX,
                                 })
            recipeActionModel.append({"ActionName":      qmltextEditRecipe,
                                 "ActionIndex":     RecipeEnum.EDIT_IDX,
                                })
            recipeActionModel.append({"ActionName":      qmltextResetCycleCount,
                                 "ActionIndex":     RecipeEnum.RESET_CYCLE_COUNT_IDX,
                                })
            recipeActionModel.append({"ActionName":      qmltextSetAsActive,
                                 "ActionIndex":     RecipeEnum.SET_AS_ACTIVE_IDX,
                                })
        }
    }

    ListModel {
        id: sequenceActionModel
        function resetModel()
        {
            sequenceActionModel.clear()
            sequenceActionModel.append({"ActionName":      qmltextProductionRun,
                                   "ActionIndex":     0,
                                   "ActionFunction":  ""
                                  })
            sequenceActionModel.append({"ActionName":      qmltextEditSequence,
                                   "ActionIndex":     1,
                                   "ActionFunction":  ""
                                  })
            sequenceActionModel.append({"ActionName":      qmltextResetCycleCount,
                                   "ActionIndex":     2,
                                   "ActionFunction":  ""
                                  })
            sequenceActionModel.append({"ActionName":      qmltextSetAsActive,
                                   "ActionIndex":     3,
                                   "ActionFunction":  ""
                                  })
        }
    }

    /****************************Test Model, will be deleted later****************************/
    Item {
        id: sequenceDataItem
        ListModel {
            id: sequenceDataModel1
            function resetModel()
            {
                sequenceDataModel1.clear()
                sequenceDataModel1.append({"TitleNum":      "4",
                                           "TitleDetails":  "Left Joint"
                                       })
                sequenceDataModel1.append({"TitleNum":      "7",
                                           "TitleDetails":  "Right Joint"
                                          })
            }
        }

        ListModel {
            id: sequenceDataModel2
            function resetModel()
            {
                sequenceDataModel2.clear()
                sequenceDataModel2.append({"TitleNum":     "5",
                                           "TitleDetails": "GoCapOuter"
                                       })
                sequenceDataModel2.append({"TitleNum":     "2",
                                           "TitleDetails": "GoCapInner"
                                       })
                sequenceDataModel2.append({"TitleNum":     "1",
                                           "TitleDetails": "GoCapSeam"
                                       })
            }
        }

        ListModel {
            id: sequenceDataModel3
            function resetModel()
            {
                sequenceDataModel3.clear()
                sequenceDataModel3.append({"TitleNum":     "10",
                                           "TitleDetails": "RecipeName"
                                          })
                sequenceDataModel3.append({"TitleNum":     "3",
                                           "TitleDetails": "RecipeName"
                                          })
            }
        }
        ListModel {
            id: sequenceDataModel
            function resetModel()
            {
                sequenceDataModel1.resetModel()
                sequenceDataModel2.resetModel()
                sequenceDataModel3.resetModel()
                sequenceDataModel.clear()
                sequenceDataModel.append({"SequenceDetailsModel":   sequenceDataModel1,
                                        "AssignedNum":          "S5",
                                        "AssignedName":         "Shield",
                                        "CycleTitle":           "Sequence Count",
                                        "CycleValue":           "1",
                                        "IsNewCard":            true
                                       })
                sequenceDataModel.append({"SequenceDetailsModel":   sequenceDataModel1,
                                        "AssignedNum":          "S5",
                                        "AssignedName":         "Shield",
                                        "CycleTitle":           "Sequence Count",
                                        "CycleValue":           "1",
                                        "IsNewCard":            false
                                       })
                sequenceDataModel.append({"SequenceDetailsModel":   sequenceDataModel2,
                                        "AssignedNum":          "S4",
                                        "AssignedName":         "GoCap",
                                        "CycleTitle":           "Sequence Count",
                                        "CycleValue":           "2",
                                        "IsNewCard":            false
                                       })
                sequenceDataModel.append({"SequenceDetailsModel":   sequenceDataModel3,
                                        "AssignedNum":          "S3",
                                        "AssignedName":         "NosePiece",
                                        "CycleTitle":           "Sequence Count",
                                        "CycleValue":           "3",
                                        "IsNewCard":            false
                                       })
            }
        }
    }

    /*****************************************************************************************/

    Rectangle {
        id: tabBarBackground
        anchors.left: parent.left
        anchors.leftMargin: Math.round(16 * Style.scaleHint)
        anchors.top: parent.top
        width: Math.round(190 * Style.scaleHint)
        height: Math.round(47 * Style.scaleHint)
        color: Style.backgroundColor
        TabBar {
            id: recipeTabBar
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            height: Math.round(30 * Style.scaleHint)
            spacing: 26
            background: Rectangle{
                color: Style.backgroundColor
            }
            BransonTabButton {
                id: tabbtnRecipe
                width: Math.round(72 * Style.scaleHint)
                tabbtnText: qmltextTabBarRecipe
            }

//            BransonTabButton {
//                id: tabbtnSequence
//                tabbtnText: qmltextTabBarSequence
//                tabbtnEnable: recipeTabBar.currentIndex === 1 ? true : false
//            }
        }
    }

    SwipeView {
        id: recipeSwipeView
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.top: tabBarBackground.bottom
        anchors.bottom: parent.bottom
        currentIndex: recipeTabBar.currentIndex

        onCurrentIndexChanged: {
            recipeTabBar.currentIndex = recipeSwipeView.currentIndex
        }

        //Following is the classical factory design pattern for the recipe and sequence card.
        //The Viewer, Model and Delegate are three full independence components can be instantiated for the different cards regardless of Recipe card or Sequence card.
        Page {
            id: recipeGrid
            property alias model: recipeGridView.gridViewModel
            BransonGridView {
                id: recipeGridView
                anchors.fill: parent
                gridViewModel: recipeModel
                gridViewDelegate: recipeDelegate
                gridViewCellHeight: Math.round(parent.height / 2.2)
                gridViewCellWidth: Math.round(parent.width / 2)
            }
            Component {
                id: recipeDelegate
                BransonNewCard {
                    id: recipeCard
                    width: recipeGridView.gridViewCellWidth - 10
                    height: recipeGridView.gridViewCellHeight - 10
                    actionModel: recipeActionModel
                    strDataModel: recipeDataModel
                    numberAssigned: model.assignedNum
                    nameAssigned:   model.assignedName
                    weldCountTitle: qmltextCycleCount
                    weldCountValue: model.cycleCount
                    isActive:       model.isActive
                    isNewCard:      model.isNewCard
                    qmltextAction:  qmltextActions
                    qmltextNewCard: qmltextNewRecipe

                    ListModel {
                        id: recipeDataModel
                        Component.onCompleted: {
                            recipeDataModel.append({"TitleNum": mainWindow.getWeldModeText(model.weldModeEnum),
                                              "TitleDetails": model.weldModeValue + model.weldModeUnit})
                        }
                    }

                    onSignalActionEvent: {
                        switch(actionIndex)
                        {
                        case RecipeEnum.CREATE_NEW_IDX:
                            mainWindow.menuChildOptionSelect(UIScreenEnum.RECIPES, UIScreenEnum.RECIPES_LAB)
                            recipeModel.insertRow(index)
                            break;
                        case RecipeEnum.PRODUCTION_RUN_IDX:
                            mainWindow.menuParentOptionSelect(UIScreenEnum.PRODUCTION)
                            break;
                        case RecipeEnum.EDIT_IDX:
                            mainWindow.menuChildOptionSelect(UIScreenEnum.RECIPES, UIScreenEnum.RECIPES_LAB)
                            break;
                        case RecipeEnum.RESET_CYCLE_COUNT_IDX:
                            recipeModel.resetCycleCount(index)
                            break;
                        case RecipeEnum.SET_AS_ACTIVE_IDX:
                            recipeModel.setAsActive(index)
                            break;
                        case RecipeEnum.DELETE_IDX:
                            recipeModel.removeRow(index)
                            break;
                        case RecipeEnum.COPY_IDX:
                            recipeModel.insertRow(index)
                            break;
                        case RecipeEnum.INFORMATION_IDX:
                            break;
                        }
                    }
                }
            }
        }

//        Page {
//            id: sequenceGrid
//            property alias model: sequenceGridView.gridViewModel
//            BransonGridView {
//                id: sequenceGridView
//                anchors.fill: parent
//                gridViewModel: sequenceDataModel
//                gridViewDelegate: sequenceDelegate
//            }
//            Component {
//                id: sequenceDelegate
//                BransonNewCard {
//                    width: sequenceGridView.gridViewCellWidth - 10
//                    height: sequenceGridView.gridViewCellHeight - 10
//                    actionModel: sequenceActionModel
//                    strDataModel: model.SequenceDetailsModel
//                    numberAssigned: model.AssignedNum
//                    nameAssigned:   model.AssignedName
//                    weldCountTitle: model.CycleTitle
//                    weldCountValue: model.CycleValue
//                    isNewCard:      model.IsNewCard
//                    qmltextAction:  qmltextActions
//                    qmltextNewCard: qmltextNewSequence
//                }
//            }
//        }


    }
}
